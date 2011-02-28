//
// Util.h
//

#pragma once

class SqlSelectCommand;

namespace FileGDBAPI
{

class Row;

/// An enumerator of rows. Used as a return type for table queries.

class EXT_FILEGDB_API EnumRows
{
public:

  /// Returns the next available row in the enumerator, or null if no rows remain.
  /// @param[out]   row The next row in the enumerator.
  /// @return       A long integer indicating whether the method finished successfully.
  long Next(Row& row);

  /// Closes the enumerator and releases any resources it is holding.
  void Close();

  /// @name Constructors and destructors
  //@{
  /// The class constructor.
  EnumRows();

  /// The class destructor.
  ~EnumRows();
  //@}

private:

  /// @cond PRIVATE
  long SetupRows(SqlSelectCommand* pSqlSelectCommand);
  bool IsSetup();

  SqlSelectCommand* m_pSqlSelectCommand;

  friend class Geodatabase;
  friend class Table;

  EnumRows(const EnumRows&) {  }

  EnumRows& operator=(const EnumRows&){ return *this; }
  /// @endcond
};

/// A utility class for working with serialized shapes.
class EXT_FILEGDB_API ShapeBuffer
{
public:

  /// Allocates a byte array of the specified size.
  /// @param[in]    length The number of bytes to allocate.
  /// @return       bool Indicates success.
  bool Allocate(unsigned long length);

  /// @name Constructors and destructors
  //@{
  /// The class constructor.
  ShapeBuffer(unsigned long length = 0);

  /// The class destructor.
  ~ShapeBuffer();
  //@}

  /// The underlying byte array.
  BYTE*           shapeBuffer;

  /// The capacity of the byte array.
  unsigned long   allocatedLength;

  /// The number of bytes being used in the array.
  unsigned long   inUseLength;

private:
  ShapeBuffer(const ShapeBuffer&) {  }

  ShapeBuffer& operator=(const ShapeBuffer&){ return *this; }
};

/// A utility class for working with database BLOBs.
class EXT_FILEGDB_API ByteArray
{
public:

  /// Allocates a byte array of the specified size.
  /// @param[in]    length The number of bytes to allocate.
  /// @return       bool Indicates success.
  bool Allocate(unsigned long length);

  /// @name Constructors and destructors
  //@{
  /// The class constructor.
  ByteArray(unsigned long length = 0);

  /// The class destructor.
  ~ByteArray();
  //@}

  /// The underlying byte array.
  BYTE*           byteArray;

  /// The capacity of the byte array.
  unsigned long   allocatedLength;

  /// The number of bytes being used in the array.
  unsigned long   inUseLength;

private:
  ByteArray(const ByteArray&) {  }

  ByteArray& operator=(const ByteArray&){ return *this; }
};

/// Defines an XY spatial extent.
class EXT_FILEGDB_API Envelope
{
public:

  /// Indicates whether the envelope's attributes have been set.
  /// @return       True if one or more attributes are NaN, false otherwise.
  bool IsEmpty();

  /// Sets the envelope's attributes to NaN.
  /// @return       Void
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
};

};  // namespace FileGDBAPI
