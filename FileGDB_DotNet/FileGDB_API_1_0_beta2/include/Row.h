//
// Row.h
//

#pragma once

struct IFields;
struct FieldValue;
class  FieldValues;

namespace FileGDBAPI
{

class ShapeBuffer;
class ByteArray;
class Raster;
class EnumRows;

/// Provides methods to get and set data on table rows.
class EXT_FILEGDB_API Row
{
public:

  /// @name Getters and setters
  //@{
  /// Indicates whether the specified field contains a null value.
  /// If the field does not exist, this will fail with an error code of -2147219885 (FIELD_NOT_FOUND).
  /// @param[in]    field The field to check for a null value.
  /// @param[out]   isNull Indicates whether the specified field contains a null value.
  /// @return       A long integer indicating whether the method finished successfully.
  long	IsNull(const std::wstring& field, bool& isNull);

  /// Assigns a null value to the specified field.
  /// If the field does not exist, this will fail with an error code of -2147219885 (FIELD_NOT_FOUND).
  /// If the field is not nullable, this will fail with an error code of -2147219879 (FIELD_NOT_NULLABLE).
  /// @param[in]    field The field to set as null.
  /// @return       A long integer indicating whether the method finished successfully.
  long SetNull(const std::wstring& field);

  /// Gets the row's Object ID.
  /// If the row's table does not have an Object ID column, this will fail with an error code of -2147219885 (FIELD_NOT_FOUND).
  /// @param[out]   objectID The row's Object ID.
  /// @return       A long integer indicating whether the method finished successfully.
  long GetOID(long& objectID);

  /// Gets the row's Global ID.
  /// If the row's table does not have an Global ID column, this will fail with an error code of -2147219885 (FIELD_NOT_FOUND).
  /// @param[out]   globalID The row's Global ID.
  /// @return       A long integer indicating whether the method finished successfully.
  long GetGlobalID(GUID& globalID);

  /// Gets the row's geometry. The buffer is a shape record as defined in the ESRI Shapefile Technical 
  /// Description, which is included in the documentation. The Editing and Querying samples write and 
  /// read a point shape buffer. Other shape types can be read based on the shapefile specification.
  /// If the row's table does not have a geometry column, this will fail with an error code of -2147219885 (FIELD_NOT_FOUND).
  /// @param[out]   shapeBuffer The row's geometry.
  /// @return       A long integer indicating whether the method finished successfully.
  long GetGeometry(ShapeBuffer& shapeBuffer);

  /// Sets the row's geometry. The buffer is a shape record as defined in the ESRI Shapefile Technical 
  /// Description, which is included in the documentation. The Editing and Querying samples write and 
  /// read a point shape buffer. If the row's table does not have a geometry column, this will fail with 
  /// an error code of -2147219885 (FIELD_NOT_FOUND). If the geometry has an invalid geometry type, this will fail with an 
  /// error code of E_FAIL.
  /// @param[in]    shapeBuffer The geometry to assign to the row.
  /// @return       A long integer indicating whether the method finished successfully.
  long SetGeometry(const ShapeBuffer& shapeBuffer);

  /// Gets a short value from the specified field.
  /// If the field does not exist, this will fail with an error code of -2147219885 (FIELD_NOT_FOUND).
  /// If the field is has an incompatible data type, this will fail with an error code of -2147217395 (FEATURE_VALUE_TYPE_MISMATCH).
  /// If the field contains a null value, this will fail with an error code of E_FAIL.
  /// @param[in]    field The name of the field to get the value from.
  /// @param[out]   value The field's value.
  /// @return       A long integer indicating whether the method finished successfully.
  long GetShort(const std::wstring& field, short& value);

  /// Assigns a short value to the specified field.
  /// If the field does not exist, this will fail with an error code of -2147219885 (FIELD_NOT_FOUND).
  /// If the field has an incompatible data type, this will fail with an error code of -2147217395 (FEATURE_VALUE_TYPE_MISMATCH).
  /// @param[in]    field The name of the field to assign the value to.
  /// @param[out]   value The value to assign to the field.
  /// @return       A long integer indicating whether the method finished successfully.
  long SetShort(const std::wstring& field, short value);

  /// Gets an integer value from the specified field.
  /// If the field does not exist, this will fail with an error code of -2147219885 (FIELD_NOT_FOUND).
  /// If the field has an incompatible data type, this will fail with an error code of -2147217395 (FEATURE_VALUE_TYPE_MISMATCH).
  /// If the field contains a null value, this will fail with an error code of E_FAIL.
  /// @param[in]    field The name of the field to get the value from.
  /// @param[out]   value The field's value.
  /// @return       A long integer indicating whether the method finished successfully.
  long GetInteger(const std::wstring& field, long& value);

  /// Assigns an integer value to the specified field.
  /// If the field does not exist, this will fail with an error code of -2147219885 (FIELD_NOT_FOUND).
  /// If the field has an incompatible data type, this will fail with an error code of -2147217395 (FEATURE_VALUE_TYPE_MISMATCH).
  /// @param[in]    field The name of the field to assign the value to.
  /// @param[out]   value The value to assign to the field.
  /// @return       A long integer indicating whether the method finished successfully.
  long SetInteger(const std::wstring& field, long value);

  /// Gets a float value from the specified field.
  /// If the field does not exist, this will fail with an error code of -2147219885 (FIELD_NOT_FOUND).
  /// If the field has an incompatible data type, this will fail with an error code of -2147217395 (FEATURE_VALUE_TYPE_MISMATCH).
  /// If the field contains a null value, this will fail with an error code of E_FAIL.
  /// @param[in]    field The name of the field to get the value from.
  /// @param[out]   value The field's value.
  /// @return       A long integer indicating whether the method finished successfully.
  long GetFloat(const std::wstring& field, float& value);

  /// Assigns a float value to the specified field.
  /// If the field does not exist, this will fail with an error code of -2147219885 (FIELD_NOT_FOUND).
  /// If the field has an incompatible data type, this will fail with an error code of -2147217395 (FEATURE_VALUE_TYPE_MISMATCH).
  /// @param[in]    field The name of the field to assign the value to.
  /// @param[out]   value The value to assign to the field.
  /// @return       A long integer indicating whether the method finished successfully.
  long SetFloat(const std::wstring& field, float value);

  /// Gets a double value from the specified field.
  /// If the field does not exist, this will fail with an error code of -2147219885 (FIELD_NOT_FOUND).
  /// If the field has an incompatible data type, this will fail with an error code of -2147217395 (FEATURE_VALUE_TYPE_MISMATCH).
  /// If the field contains a null value, this will fail with an error code of E_FAIL.
  /// @param[in]    field The name of the field to get the value from.
  /// @param[out]   value The field's value.
  /// @return       A long integer indicating whether the method finished successfully.
  long GetDouble(const std::wstring& field, double& value);

  /// Assigns a double value to the specified field.
  /// If the field does not exist, this will fail with an error code of -2147219885 (FIELD_NOT_FOUND).
  /// If the field has an incompatible data type, this will fail with an error code of -2147217395 (FEATURE_VALUE_TYPE_MISMATCH).
  /// @param[in]    field The name of the field to assign the value to.
  /// @param[out]   value The value to assign to the field.
  /// @return       A long integer indicating whether the method finished successfully.
  long SetDouble(const std::wstring& field, double value);

  /// Gets a date/time value from the specified field.
  /// If the field does not exist, this will fail with an error code of -2147219885 (FIELD_NOT_FOUND).
  /// If the field has an incompatible data type, this will fail with an error code of -2147217395 (FEATURE_VALUE_TYPE_MISMATCH).
  /// If the field contains a null value, this will fail with an error code of E_FAIL.
  /// @param[in]    field The name of the field to get the value from.
  /// @param[out]   value The field's value.
  /// @return       A long integer indicating whether the method finished successfully.
  long GetDate(const std::wstring& field, struct tm& value);

  /// Assigns a date/time value to the specified field.
  /// If the field does not exist, this will fail with an error code of -2147219885 (FIELD_NOT_FOUND).
  /// If the field has an incompatible data type, this will fail with an error code of -2147217395 (FEATURE_VALUE_TYPE_MISMATCH).
  /// @param[in]    field The name of the field to get the value from.
  /// @param[out]   value The value to assign to the field.
  /// @return       A long integer indicating whether the method finished successfully.
  long SetDate(const std::wstring& field, const struct tm& value);

  /// Gets a string value from the specified field.
  /// If the field does not exist, this will fail with an error code of -2147219885 (FIELD_NOT_FOUND).
  /// If the field has an incompatible data type, this will fail with an error code of -2147217395 (FEATURE_VALUE_TYPE_MISMATCH).
  /// If the field contains a null value, this will fail with an error code of E_FAIL.
  /// @param[in]    field The name of the field to get the value from.
  /// @param[out]   value The field's value.
  /// @return       A long integer indicating whether the method finished successfully.
  long GetString(const std::wstring& field, std::wstring& value);

  /// Assigns a string value to the specified field.
  /// If the field does not exist, this will fail with an error code of -2147219885 (FIELD_NOT_FOUND).
  /// If the field has an incompatible data type, this will fail with an error code of -2147217395 (FEATURE_VALUE_TYPE_MISMATCH).
  /// @param[in]    field The name of the field to assign the value to.
  /// @param[out]   value The value to assign to the field.
  /// @return       A long integer indicating whether the method finished successfully.
  long SetString(const std::wstring& field, const std::wstring& value);

  /// Gets a GUID value from the specified field.
  /// If the field does not exist, this will fail with an error code of -2147219885 (FIELD_NOT_FOUND).
  /// If the field has an incompatible data type, this will fail with an error code of -2147217395 (FEATURE_VALUE_TYPE_MISMATCH).
  /// If the field contains a null value, this will fail with an error code of E_FAIL.
  /// @param[in]    field The name of the field to get the value from.
  /// @param[out]   value The field's value.
  /// @return       A long integer indicating whether the method finished successfully.
  long GetGUID(const std::wstring& field, GUID& value);

  /// Assigns a GUID value to the specified field.
  /// If the field does not exist, this will fail with an error code of -2147219885 (FIELD_NOT_FOUND).
  /// If the field has an incompatible data type, this will fail with an error code of -2147217395 (FEATURE_VALUE_TYPE_MISMATCH).
  /// @param[in]    field The name of the field to assign the value to.
  /// @param[out]   value The value to assign to the field.
  /// @return       A long integer indicating whether the method finished successfully.
  long SetGUID(const std::wstring& field, GUID value);

  /// Gets an XML value from the specified field.
  /// If the field does not exist, this will fail with an error code of -2147219885 (FIELD_NOT_FOUND).
  /// If the field has an incompatible data type, this will fail with an error code of -2147217395 (FEATURE_VALUE_TYPE_MISMATCH).
  /// If the field contains a null value, this will fail with an error code of E_FAIL.
  /// @param[in]    field The name of the field to get the value from.
  /// @param[out]   value The field's value.
  /// @return       A long integer indicating whether the method finished successfully.
  long GetXML(const std::wstring& field, std::string& value);

  /// Assigns an XML value to the specified field.
  /// If the field does not exist, this will fail with an error code of -2147219885 (FIELD_NOT_FOUND).
  /// If the field has an incompatible data type, this will fail with an error code of -2147217395 (FEATURE_VALUE_TYPE_MISMATCH).
  /// @param[in]    field The name of the field to assign the value to.
  /// @param[out]   value The value to assign to the field.
  /// @return       A long integer indicating whether the method finished successfully.
  long SetXML(const std::wstring& field, const std::string& value);

  /// Gets a raster from the specified field.
  /// If the field does not exist, this will fail with an error code of -2147219885 (FIELD_NOT_FOUND).
  /// If the field has an incompatible data type, this will fail with an error code of -2147217395 (FEATURE_VALUE_TYPE_MISMATCH).
  /// @param[in]    field The name of the field to get the value from.
  /// @param[out]   raster The field's value.
  /// @return       A long integer indicating whether the method finished successfully.
  long GetRaster(const std::wstring& field, Raster& raster);

  /// Assigns a raster to the specified field.
  /// If the field does not exist, this will fail with an error code of -2147219885 (FIELD_NOT_FOUND).
  /// If the field has an incompatible data type, this will fail with an error code of -2147217395 (FEATURE_VALUE_TYPE_MISMATCH).
  /// @param[in]    field The name of the field to assign the value to.
  /// @param[out]   raster The value to assign to the field.
  /// @return       A long integer indicating whether the method finished successfully.
  long SetRaster(const std::wstring& field, const Raster& raster);

  /// Gets a byte array from the specified field.
  /// If the field does not exist, this will fail with an error code of -2147219885 (FIELD_NOT_FOUND).
  /// If the field has an incompatible data type, this will fail with an error code of -2147217395 (FEATURE_VALUE_TYPE_MISMATCH).
  /// If the field contains a null value, this will fail with an error code of E_FAIL.
  /// @param[in]    field The name of the field to get the value from.
  /// @param[out]   binaryBuf The field's value.
  /// @return       A long integer indicating whether the method finished successfully.
  long GetBinary(const std::wstring& field, ByteArray& binaryBuf);

  /// Assigns a byte array to the specified field.
  /// If the field does not exist, this will fail with an error code of -2147219885 (FIELD_NOT_FOUND).
  /// If the field has an incompatible data type, this will fail with an error code of -2147217395 (FEATURE_VALUE_TYPE_MISMATCH).
  /// @param[in]    field The name of the field to assign the value to.
  /// @param[out]   binaryBuf The value to assign to the field.
  /// @return       A long integer indicating whether the method finished successfully.
  long SetBinary(const std::wstring& field, const ByteArray& binaryBuf);
  //@}

  /// @name Constructors and Destructors
  //@{
  /// The class constructor.
  Row();

  /// The class destructor.
  ~Row();
  //@}

private:

  /// @cond PRIVATE
  long SetupRow(IFields* pFields, FieldValues* pFieldValues, bool takeOwnership);
  bool IsSetup();

  long FindField(const std::wstring& field, long& fieldNumber, long& fieldType);
  long IsNullable(long fieldNumber, bool& isNullable);

  long SetOID(long objectID);
  long SetGlobalID(GUID globalID);

  long                m_numFields;
  long*               m_pFieldMap;
  FieldValue*         m_pValues;
  long                m_oidFieldNumber;
  long                m_globalIDFieldNumber;
  long                m_shpFieldNumber;
  IFields*            m_pFields;

  FieldValues*        m_pFieldValues;
  bool                m_ownsFieldValues;

  friend class EnumRows;
  friend class Table;


  Row(const Row&){}
  Row& operator=(const Row&){ return *this; }
  /// @endcond
};

};  // namespace FileGDBAPI
