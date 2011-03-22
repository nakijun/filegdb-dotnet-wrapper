//
// Util.h
//

#pragma once

#include <string>

#ifndef EXPORT_FILEGDB_API
#  define EXT_FILEGDB_API _declspec(dllimport)
#else
# ifdef linux
#  define EXT_FILEGDB_API __attribute__((visibility("default")))
# else
#  define EXT_FILEGDB_API _declspec(dllexport)
#endif
#endif

#include "FileGDBCore.h"

class SqlSelectCommand;

namespace FileGDBAPI
{

class Row;
class FieldInfo;
class Point;

/// An enumerator of rows. Used as a return type for table queries.

class EXT_FILEGDB_API EnumRows
{
public:

  /// Returns the next available row in the enumerator, or null if no rows remain.
  /// @param[out]   row The next row in the enumerator.
  /// @return       Error code indicating whether the method finished successfully.
  fgdbError Next(Row& row);

  /// Closes the enumerator and releases any resources it is holding.
  void Close();

  /// Return information about the fields in the row.
  /// @param[out]   fieldInfo The field information.
  /// @return       Error code indicating whether the method finished successfully.
  fgdbError GetFieldInformation(FieldInfo& fieldInfo);

  /// @name Constructors and destructors
  //@{
  /// The class constructor.
  EnumRows();

  /// The class destructor.
  ~EnumRows();
  //@}

private:

  /// @cond PRIVATE
  fgdbError SetupRows(SqlSelectCommand* pSqlSelectCommand);
  bool      IsSetup();

  SqlSelectCommand* m_pSqlSelectCommand;

  friend class Geodatabase;
  friend class Table;

  EnumRows(const EnumRows&)             { }
  EnumRows& operator=(const EnumRows&)  { return *this; }
  /// @endcond
};

/// A utility class for providing field information.
class EXT_FILEGDB_API FieldInfo
{
public:

  /// The number of fields.
  /// @param[out]   fieldCount The number of fields.
  /// @return       Error code indicating whether the method finished successfully.
  fgdbError GetFieldCount(int& fieldCount);

  /// The name of the field.
  /// @param[in]    fieldNumber The number of field.
  /// @param[out]   fieldName The name of the field.
  /// @return       Error code indicating whether the method finished successfully.
  fgdbError GetFieldName(int fieldNumber, std::wstring& fieldName);

  /// The data type of the field.
  /// @param[in]    fieldNumber The number of field.
  /// @param[out]   fieldType The data type of the field.
  /// @return       Error code indicating whether the method finished successfully.
  fgdbError GetFieldType(int fieldNumber, FieldType& fieldType);

  /// The length of the field.
  /// @param[in]    fieldNumber The number of field.
  /// @param[out]   fieldLength The length of the field.
  /// @return       Error code indicating whether the method finished successfully.
  fgdbError GetFieldLength(int fieldNumber, int& fieldLength);

  /// The nullability of the field.
  /// @param[in]    fieldNumber The number of field.
  /// @param[out]   isNullable The nullability of the field.
  /// @return       Error code indicating whether the method finished successfully.
  fgdbError GetFieldIsNullable(int fieldNumber, bool& isNullable);

  /// @name Constructors and destructors
  //@{
  /// The class constructor.
  FieldInfo();

  /// The class destructor.
  ~FieldInfo();
  //@}

private:

  fgdbError SetupFieldInfo(IFields* pFields);
  bool      IsSetup();

  IFields*            m_pFields;

  friend class EnumRows;
  friend class Table;
  friend class Row;

  FieldInfo(const FieldInfo&)             { }
  FieldInfo& operator=(const FieldInfo&)  { return *this; }
};

/// A utility class for working with serialized shapes.
class EXT_FILEGDB_API ShapeBuffer
{
public:

  /// Allocates a byte array of the specified size.
  /// @param[in]    length The number of bytes to allocate.
  /// @return       bool Indicates success.
  bool Allocate(size_t length);

  /// @name Constructors and destructors
  //@{
  /// The class constructor.
  ShapeBuffer(size_t length = 0);

  /// The class destructor.
  virtual ~ShapeBuffer();
  //@}

  /// The underlying byte array.
  byte*           shapeBuffer;

  /// The capacity of the byte array.
  size_t          allocatedLength;

  /// The number of bytes being used in the array.
  size_t          inUseLength;

  bool      IsEmpty(void);
  void      SetEmpty(void);

  fgdbError GetShapeType(int& shapeType);

  static bool HasZs(int shapeType);
  static bool HasMs(int shapeType);
  static bool HasIDs(int shapeType);
  static bool HasCurves(int shapeType);
  static bool HasNormals(int shapeType);
  static bool HasTextures(int shapeType);
  static bool HasMaterials(int shapeType);

  static int  GeometryType(int shapeType);

private:

  ShapeBuffer(const ShapeBuffer&)             { }
  ShapeBuffer& operator=(const ShapeBuffer&)  { return *this; }
};

class EXT_FILEGDB_API PointShapeBuffer : public ShapeBuffer
{
public:

  fgdbError GetPoints(Point*& xyArray);
  fgdbError GetZs(double*& zArray);
  fgdbError GetMs(double*& mArray);
  fgdbError GetIDs(int*& idArray);

  fgdbError Setup(int shapeType);
};

class EXT_FILEGDB_API MultiPointShapeBuffer : public ShapeBuffer
{
public:

  fgdbError GetExtent(double*& extent);
  fgdbError GetNumPoints(int& numPoints);
  fgdbError GetPoints(Point*& xyArray);
  fgdbError GetZExtent(double*& zExtent);
  fgdbError GetZs(double*& zArray);
  fgdbError GetMExtent(double*& mExtent);
  fgdbError GetMs(double*& mArray);
  fgdbError GetIDs(int*& idArray);

  fgdbError Setup(int shapeType, int numPoints);

  fgdbError CalculateExtent(void);
};

class EXT_FILEGDB_API MultiPartShapeBuffer : public ShapeBuffer
{
public:

  fgdbError GetExtent(double*& extent);
  fgdbError GetNumParts(int& numParts);
  fgdbError GetNumPoints(int& numPoints);
  fgdbError GetParts(int*& partArray);
  fgdbError GetPoints(Point*& xyArray);
  fgdbError GetZExtent(double*& zExtent);
  fgdbError GetZs(double*& zArray);
  fgdbError GetMExtent(double*& mExtent);
  fgdbError GetMs(double*& mArray);
  fgdbError GetNumCurves(int& numCurves);
  fgdbError GetCurves(byte*& curves);
  fgdbError GetIDs(int*& idArray);

  fgdbError Setup(int shapeType, int numParts, int numPoints, int numCurves);

  fgdbError CalculateExtent(void);
};

class EXT_FILEGDB_API MultiPatchShapeBuffer : public ShapeBuffer
{
public:

  fgdbError GetExtent(double*& extent);
  fgdbError GetNumParts(int& numParts);
  fgdbError GetNumPoints(int& numPoints);
  fgdbError GetParts(int*& partArray);
  fgdbError GetPartDescriptors(int*& partDescriptorArray);
  fgdbError GetPoints(Point*& xyArray);
  fgdbError GetZExtent(double*& zExtent);
  fgdbError GetZs(double*& zArray);
  fgdbError GetMExtent(double*& mExtent);
  fgdbError GetMs(double*& mArray);
  fgdbError GetIDs(int*& idArray);
  //fgdbError GetMultipatchProperties(normals, textures, materials);

  fgdbError Setup(int shapeType, int numParts, int numPoints, int numCurves);

  fgdbError CalculateExtent(void);
};

/// A utility class for working with database BLOBs.
class EXT_FILEGDB_API ByteArray
{
public:

  /// Allocates a byte array of the specified size.
  /// @param[in]    length The number of bytes to allocate.
  /// @return       bool Indicates success.
  bool Allocate(size_t length);

  /// @name Constructors and destructors
  //@{
  /// The class constructor.
  ByteArray(size_t length = 0);

  /// The class destructor.
  ~ByteArray();
  //@}

  /// The underlying byte array.
  byte*           byteArray;

  /// The capacity of the byte array.
  size_t          allocatedLength;

  /// The number of bytes being used in the array.
  size_t          inUseLength;

private:

  ByteArray(const ByteArray&)             { }
  ByteArray& operator=(const ByteArray&)  { return *this; }
};

/// Defines an XY spatial extent.
class EXT_FILEGDB_API Envelope
{
public:

  /// Indicates whether the envelope's attributes have been set.
  /// @return       True if one or more attributes are NaN, false otherwise.
  bool IsEmpty();

  /// Sets the envelope's attributes to NaN.
  /// @return       Void.
  void SetEmpty();

  /// @name Constructors and destructors
  //@{
  /// The class constructors.
  Envelope();
  Envelope(double xmin, double xmax, double ymin, double ymax);

  /// The class destructor.
  ~Envelope();
  //@}

  /// The lower X boundary of the envelope.
  double          xMin;

  /// The lower Y boundary of the envelope.
  double          yMin;

  /// The upper X boundary of the envelope.
  double          xMax;

  /// The upper Y boundary of the envelope.
  double          yMax;

  /// The lower Z boundary of the envelope.
  double          zMin;

  /// The upper Z boundary of the envelope.
  double          zMax;
};

class EXT_FILEGDB_API Point
{
public:

  double          x;
  double          y;
};

/// Provides access to error text and extended error information.
namespace ErrorInfo
{
  /// Returns the text error message which corresponds to an error code.
  /// If there is no description corresponding to the error code, the error
  /// description string will be empty and a 1 (S_FALSE) error will be returned.
  /// @param[in]    fgdbError The error code to look up.
  /// @param[out]   errorDescription The description of the error.
  /// @return       Error code indicating whether the method finished successfully.
  EXT_FILEGDB_API fgdbError GetErrorDescription(fgdbError fgdbError, std::wstring& errorDescription);

  /// Returns the number of error records in the error stack.
  /// @param[out]   recordCount The number of error records.
  /// @return       Void.
  EXT_FILEGDB_API void GetErrorRecordCount(int& recordCount);

  /// Returns an error record.
  /// @param[in]    recordNum The error record to return.
  /// @param[out]   fgdbError The error code.
  /// @param[out]   errorDescription The description of the error.
  /// @return       Error code indicating whether the method finished successfully.
  EXT_FILEGDB_API fgdbError GetErrorRecord(int recordNum, fgdbError& fgdbError, std::wstring& errorDescription);

  /// Clears the error stack.
  /// @return       Void.
  EXT_FILEGDB_API void ClearErrors(void);
};

/// Provides access to spatial reference information.

struct SpatialReferenceInfo
{
  std::wstring  auth_name;    // The name of the standard or standards body that is being cited for this reference system.
  int           auth_srid;    // The ID of the Spatial Reference System as defined by the Authority cited in AUTH_NAME.
  std::wstring  srtext;       // The Well-known Text Representation of the Spatial Reference System.
  std::wstring  srname;       // The name of the Spatial Reference System.
};

class EXT_FILEGDB_API EnumSpatialReferenceInfo
{
public:

  EnumSpatialReferenceInfo();
  ~EnumSpatialReferenceInfo();

  bool NextGeographicSpatialReference(SpatialReferenceInfo& spatialReferenceInfo);
  bool NextProjectedSpatialReference(SpatialReferenceInfo& spatialReferenceInfo);
  void Reset();

private:

  int           m_currentGCS;
  int           m_currentPCS;
};

namespace SpatialReferences
{
  /// Returns information about a spatial reference given its AUTH_SRID.
  /// @param[in]    auth_srid The AUTH_SRID of the spatial reference to find.
  /// @param[out]   spatialRef The properties of the requested spatial reference.
  /// @return       Error code indicating whether the method finished successfully.
  EXT_FILEGDB_API bool FindSpatialReferenceBySRID(int auth_srid, SpatialReferenceInfo& spatialRef);

  /// Returns information about a spatial reference given its name.
  /// @param[in]    srname The name of the spatial reference to find.
  /// @param[out]   spatialRef The properties of the requested spatial reference.
  /// @return       Error code indicating whether the method finished successfully.
  EXT_FILEGDB_API bool FindSpatialReferenceByName(const std::wstring& srname, SpatialReferenceInfo& spatialRef);
};

};  // namespace FileGDBAPI
