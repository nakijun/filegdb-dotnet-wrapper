//
// Table.h
//

#pragma once

class Datafile;

namespace FileGDBAPI
{

class EnumRows;
class Envelope;
class Row;
class Geodatabase;

/// Provides methods to work with tables, such as querying and modifying both schema and data.
class EXT_FILEGDB_API Table
{
public:

  /// @name Schema
  //@{
  /// Gets the table's definition as an XML document.
  /// @param[out]   tableDef An XML document than defines the table's schema.
  /// @return       A long integer indicating whether the method finished successfully.
  long GetDefinition(std::string& tableDef);

  /// Gets the table's metadata as XML.
  /// @param[out]   documentation The table's metadata as XML.
  /// @return       A long integer indicating whether the method finished successfully.
  long GetDocumentation(std::string& documentation);

  /// Assigns metadata to the table.
  /// @param[in]    documentation An XML document that will be the table's metadata.
  /// @return       A long integer indicating whether the method finished successfully.
  long SetDocumentation(const std::string& documentation);

  /// Adds a field to the table.
  /// If the XML is not UTF-8 encoded, create will fail with an error code of -2147024809 (INVALIDARG).<br/>
  /// If you are adding an OBJECTID field and one already exists, a -2147219707 (FIELDS_MULTIPLE_OIDS) 
  /// error will be returned . Only one OBJECTID field is allowed.<br/>
  /// If you are adding an GLOBALID field and one already exists, a -2147219703 (FIELDS_MULTIPLE_GLOBALIDS) 
  /// error will be returned . Only one GLOBALID field is allowed.<br/>
  /// If you attempt to add a NOT NULLABLE field to a table already contains rows, 
  /// a -2147219879 (FIELD_NOT_NULLABLE) will be returned. <br/>
  /// If the field already exists, a -2147219884 (FIELD_ALREADY_EXISTS) will be returned.<br/>
  /// <a href="esriFieldTypes.txt">FieldTypes</a>   <a href="Field.xml">XML</a>
  /// @param[in]    fieldDef An XML document defining the field's properties.
  /// @return       A long integer indicating whether the method finished successfully.
  long AddField(const std::string& fieldDef);

  /// Modifies a field in the table.
  /// If the XML is not UTF-8 encoded, create will fail with an error code of -2147024809 (INVALIDARG).<br/>
  /// @param[in]    fieldDef An XML document defining the field's properties.
  /// @return       A long integer indicating whether the method finished successfully.
  long AlterField(const std::string& fieldDef);

  /// Deletes a field from the table.
  /// If the field does not exist, an -2147219885 (FIELD_NOT_FOUND) error will be returned.<br/>
  /// @param[in]    fieldName The name of the field to delete.
  /// @return       A long integer indicating whether the method finished successfully.
  long DeleteField(const std::wstring& fieldName);

  /// Returns an XML definition of the table's index collection.
  /// @param[out]   indexes An XML document containing a collection of index definitions.
  /// @return       A long integer indicating whether the method finished successfully.
  long GetIndexes(std::vector<std::string>& indexDefs);

  /// Adds an index to the table.
  /// If the XML is not UTF-8 encoded, create will fail with an error code of -2147024809 (INVALIDARG).<br/>
  /// <a href="Index.xml">XML</a>
  /// @param[in]    indexDef An XML document defining the index's properties.
  /// @return       A long integer indicating whether the method finished successfully.
  long AddIndex(const std::string& indexDef);

  /// Deletes an index from the table.
  /// If the index is not found, an -2147219629 (INDEX_NOT_FOUND) error will be returned.<br/>
  /// @param[in]    indexName The name of the index to delete.
  /// @return       A long integer indicating whether the method finished successfully.
  long DeleteIndex(const std::wstring& indexName);

  /// Creates a new subtype to the table.
  /// If the XML is not UTF-8 encoded, create will fail with an error code of -2147024809 (INVALIDARG).<br/>
  /// <a href="SubType.xml">XML</a>
  /// @param[in]    subtypeDef An XML document defining the subtype's properties.
  /// @return       A long integer indicating whether the method finished successfully.
  long CreateSubtype(const std::string& subtypeDef);

  /// Modifies an existing subtype of the table.
  /// If the XML is not UTF-8 encoded, create will fail with an error code of -2147024809 (INVALIDARG).<br/>
  /// @param[in]    subtypeDef An XML document defining the subtype's properties.
  /// @return       A long integer indicating whether the method finished successfully.
  long AlterSubtype(const std::string& subtypeDef);

  /// Deletes a subtype from the table.
  /// @param[in]    subtypeName The name of the subtype to delete.
  /// @return       A long integer indicating whether the method finished successfully.
  long DeleteSubtype(const std::wstring& subtypeName);

  /// Enables subtypes on a table.
  /// If the XML is not UTF-8 encoded, create will fail with an error code of -2147024809 (INVALIDARG).<br/>
  /// <a href="esriFieldTypes.txt">FieldTypes</a>   <a href="Field.xml">XML</a>
  /// @param[in]    subtypeFieldName The field to use as the subtype field.
  /// @param[in]   subtypeDef The field to use as the subtype Def.
  /// @return       A long integer indicating whether the method finished successfully.
  long EnableSubtypes(const std::wstring& subtypeFieldName, const std::string& subtypeDef);

  /// Returns the default subtype code.
  /// @param[out]   defaultCode The table's default subtype code.
  /// @return       A long integer indicating whether the method finished successfully.
  long GetDefaultSubtypeCode(int& defaultCode);

  /// Sets the default subtype code.
  /// @param[out]   defaultCode The code to assign as the default subtype code.
  /// @return       A long integer indicating whether the method finished successfully.
  long SetDefaultSubtypeCode(int defaultCode);

  /// Drops the table's subtypes.
  /// @return       A long integer indicating whether the method finished successfully.
  long DisableSubtypes();
  //@}

  /// @name Data
  //@{
  /// Performs a spatial query (envelope intersects) on the table.
  /// @param[in]    subfields (Optional) The fields that should be fetched by the query's returned rows. Must 
  /// include a comma delimited list of fields or a "*". Passing in blank will return a -2147220985 (INVALID_SQL) error.
  /// @param[in]    whereClause (Optional) Attribute constraints to apply to the query.
  /// @param[in]    envelope The spatial extent of the query.
  /// @param[in]    recycling Indicates whether row memory should be recycled.
  /// @param[out]   rows The results of the query.
  /// @return       A long integer indicating whether the method finished successfully.
  long Search(const std::wstring& subfields, const std::wstring& whereClause, Envelope envelope, bool recycling, EnumRows& rows);

  /// Performs an attribute query on the table.
  /// @param[in]    subfields (Optional) The fields that should be fetched by the query's returned rows. Must 
  /// include a comma delimited list of fields or a "*". A blank will return a -2147220985 (INVALID_SQL) error.  
  /// @param[in]    whereClause (Optional) Attribute constraints to apply to the query.
  /// @param[in]    recycling Indicates whether row memory should be recycled.
  /// @param[out]   rows The results of the query.
  /// @return       A long integer indicating whether the method finished successfully.
  long Search(const std::wstring& subfields, const std::wstring& whereClause, bool recycling, EnumRows& rows);

  /// Creates a new row in memory for the table.
  /// @param[out]   row The newly-created row.
  /// @return       A long integer indicating whether the method finished successfully.
  long CreateRowObject(Row& row);

  /// Inserts a newly-created and populated row into the table.
  /// @param[in]    row The row to insert.
  /// @return       A long integer indicating whether the method finished successfully.
  long Insert(Row& row);

  /// Updates an existing row in the table.
  /// @param[in]    row The row to update.
  /// @return       A long integer indicating whether the method finished successfully.
  long Update(Row& row);

  /// Deletes a row from the table.
  /// @param[in]    row The row to delete.
  /// @return       A long integer indicating whether the method finished successfully.
  long Delete(Row& row);

  /// Indicates whether the table should be edited.
  /// @param[out]   isEditable True if the table can safely be edited.
  /// @return       A long integer indicating whether the method finished successfully.
  long IsEditable(bool& isEditable);

  /// Returns the number of rows in the table.
  /// @param[out]   rowCount The number of rows in the table.
  /// @return       A long integer indicating whether the method finished successfully.
  long GetRowCount(long& rowCount);

  /// Returns the extent of the feature class.
  /// If the table is not a feature class an error of 1 will be returned.
  /// @param[out]   extent The extent of the feature class.
  /// @return       A long integer indicating whether the method finished successfully.
  long GetExtent(Envelope& extent);
  //@}

  /// @name Constructors and destructors
  //@{
  /// The class constructor.
  Table();

  /// The class destructor.
  ~Table();
  //@}

private:

  /// @cond PRIVATE
  long SetupTable(const std::wstring& path, Geodatabase* pGeodatabase, Datafile* pDatafile);
  bool IsSetup();

  Geodatabase*    m_pGeodatabase;
  Datafile*       m_pDatafile;
  std::wstring    m_Path;

  friend class    Geodatabase;

  Table(const Table&)             { }
  Table& operator=(const Table&)  { return *this; }
  /// @endcond
};

};  // namespace FileGDBAPI
