//
// Geodatabase.h
//

#pragma once

////////////////////////////////////////////////////////////////////////////////

#include <map>

struct ci_less : std::binary_function<std::wstring, std::wstring, bool>
{
  // case insensitive (ci) string less_than
  // returns true if s1 < s2

  // case-independent (ci) compare_less binary function
  struct nocase_compare : public std::binary_function<wchar_t, wchar_t, bool>
  {
    bool operator() (const wchar_t& c1, const wchar_t& c2) const
    {
      return towlower(c1) < towlower(c2);
    }
  };

  bool operator() (const std::wstring & s1, const std::wstring & s2) const
  {
    return std::lexicographical_compare(s1.begin(), s1.end(),  // source range
                                        s2.begin(), s2.end(),  // dest range
                                        nocase_compare());     // comparison
  }
};

class Catalog;
class CatalogRef;

////////////////////////////////////////////////////////////////////////////////

namespace FileGDBAPI
{

class EnumRows;
class Row;
class Table;

/// A class representing a File Geodatabase.
class EXT_FILEGDB_API Geodatabase
{
public:

  /// @name Schema browsing
  //@{
  /// Gets a list of the dataset types in the geodatabase.
  /// @param[out]   datasetTypes The dataset types in the geodatabase.
  /// @return       A long integer indicating whether the method finished successfully.
  long GetDatasetTypes(std::vector<std::wstring>& datasetTypes);

  /// Gets a list of relationship types in the geodatabase.
  /// @param[out]   relationshipTypes The relationship types in the geodatabase.
  /// @return       A long integer indicating whether the method finished successfully.
  long GetDatasetRelationshipTypes(std::vector<std::wstring>& relationshipTypes);

  /// Gets the child datasets for a particular dataset, if any.
  /// If a non-existent path is provided, a -2147211775 (ITEM_NOT_FOUND) error will be returned.
  /// @param[in]    parentPath The dataset to find the children of, e.g. "\usa".
  /// @param[in]    datasetType The child dataset type as a wstring, e.g. "Feature Class". Passing in 
  /// an empty string will return all child datasets. <a href="ItemTypes.txt">DatasetType</a>
  /// @param[out]   childDatasets The children of the parent dataset, if any.
  /// @return       A long integer indicating whether the method finished successfully.
  long GetChildDatasets(const std::wstring& parentPath, const std::wstring& datasetType, std::vector<std::wstring>& childDatasets);

  /// Gets the related datasets for a particular dataset, if any.
  /// If a non-existent path is provided, a -2147211775 (ITEM_NOT_FOUND) error will be returned.
  /// @param[in]    path The path of the dataset to find related datasets for, e.g. "\usa\streets_topology".
  /// @param[in]    relType The relationship type to filter return values with, e.g. "DatasetInFeatureDataset". Passing in 
  /// an empty string will return all related datasets. <a href="RelationshipTypes.txt">RelationshipType</a>
  /// @param[in]    datasetType The type of the dataset to find related datasets for. <a href="ItemTypes.txt">DatasetType</a>
  /// @param[out]   relatedDatasets The origin dataset's related datasets, if any.
  /// @result       A long integer indicating whether the method finished successfully.
  long GetRelatedDatasets(const std::wstring& path, const std::wstring& relType, const std::wstring& datasetType, std::vector<std::wstring>& relatedDatasets);
  //@}

  /// @name Schema definition
  //@{
  /// Gets the definition of a dataset as an XML document.
  /// If the dataset does not exist, this will fail with an error code of -2147220655 (TABLE_NOT_FOUND).
  /// If a non-existent path is provided, a -2147211775 (ITEM_NOT_FOUND) error will be returned.
  /// @param[in]    path The requested dataset's path. e.g. "\usa\city_anno"
  /// @param[in]    datasetType The requested dataset's type as a string, e.g. "Table".  <a href="ItemTypes.txt">DatasetType</a>
  /// @param[out]   datasetDef The dataset's definition as an XML document.
  /// @return       A long integer indicating whether the method finished successfully.
  long GetDatasetDefinition(const std::wstring& path, const std::wstring& datasetType, std::string& datasetDef);

  /// Gets the definitions of child datasets as a collection of XML documents.
  /// If a non-existent path is provided, a -2147211775 (ITEM_NOT_FOUND) error will be returned.
  /// @param[in]    parentPath The parent dataset's path, e.g. "\usa".
  /// @param[in]    datasetType The parent dataset's type as a string, e.g. "Feature Dataset". Passing in 
  /// an empty string will return all child datasets. <a href="ItemTypes.txt">DatasetType</a>
  /// @param[out]   childDatasetDefs A collection of child dataset definitions, if any.
  /// @return       A long integer indicating whether the method finished successfully.
  long GetChildDatasetDefinitions(const std::wstring& parentPath, const std::wstring& datasetType, std::vector<std::string>& childDatasetDefs);

  /// Gets the definitions of related datasets as a collection of XML documents.
  /// If a non-existent path is provided, a -2147211775 (ITEM_NOT_FOUND) error will be returned.
  /// @param[in]    path The origin dataset's path, e.g. "\usa\streets_topology"
  /// @param[in]    relType The relationship type to filter return values with, e.g. "DatasetInFeatureDataset". <a href="RelationshipTypes.txt">RelationshipType</a>
  /// @param[in]    datasetType The origin dataset's type as a string, e.g. "Relationship Class". Passing in 
  /// an empty string will return all related datasets. <a href="ItemTypes.txt">DatasetType</a>
  /// @param[out]   relatedDatasetDefs A collection of related dataset definitions, if any.
  /// @return       A long integer indicating whether the method finished successfully.
  long GetRelatedDatasetDefinitions(const std::wstring& path, const std::wstring& relType, const std::wstring& datasetType, std::vector<std::string>& relatedDatasetDefs);

  /// Gets the metadata of a dataset as XML.
  /// If a non-existent path is provided, a -2147211775 (ITEM_NOT_FOUND) error will be returned.
  /// @param[in]    path The requested dataset's path. e.g. "\address_list"
  /// @param[in]    datasetType The requested dataset's type as a string, e.g. "Table". <a href="ItemTypes.txt">DatasetType</a>
  /// @param[out]   documentation The dataset's metadata as XML.
  /// @return       A long integer indicating whether the method finished successfully.
  long GetDatasetDocumentation(const std::wstring& path, const std::wstring& datasetType, std::string& documentation);
  //@}

  /// @name Datasets
  //@{
  /// Creates a new feature dataset. 
  /// If the feature dataset already exists, a -2147220733 (DATASET_ALREADY_EXISTS) error will be returned.<br/>
  /// If the feature dataset name is missing from the XML, a -2147220645 (INVALID_NAME) error will be returned.<br/>
  /// If the XML is not UTF-8 encoded, create will fail with an error code of -2147024809 (INVALIDARG).<br/>
  /// <a href="FeatureDataset.xml">XML</a>
  /// <br><br>
  /// @param[in]    featureDatasetDef The XML definition of the feature dataset to be created.
  /// @return       A long integer indicating whether the method finished successfully.
  long CreateFeatureDataset(const std::string& featureDatasetDef);

  /// Creates a new table. This can either be a table or a feature class.<br/>
  /// If the table already exists, a -2147220653 (TABLE_ALREADY_EXISTS) error will be returned.<br/>
  /// If the table name is missing from the XML, a -2147220645 (INVALID_NAME) error will be returned.<br/>
  /// If the XML is not UTF-8 encoded, create will fail with an error code of -2147024809 (INVALIDARG).<br/>
  /// <br><a href="Table.xml">XML-Table</a><br><a href="FC_GCS_Line.xml">XML-Feature Class</a>
  /// @param[in]    tableDef The XML definition of the table to be created.
  /// @param[in]    parent The location where the table will be created. Pass an empty string if you want to 
  /// create a table or feature class at the root. If you want to create a feature class in an existing feature 
  /// dataset use the path "\USA".
  /// @param[out]   table An Table instance for the newly created table.
  /// @return       A long integer indicating whether the method finished successfully.
  long CreateTable(const std::string& tableDef, const std::wstring& parent, Table& table);

  /// Opens a table. This can also be used open attributed and M:N relationship class tables.
  /// If the table does not exist, a -2147220655 (TABLE_NOT_FOUND) error will be returned.
  /// @param[in]    path The path of the table to open. Opening a table or feature class at 
  /// the root make sure to include "\". If opening a feature class in a feature dataset include 
  /// the feature dataset name in the path "\USA\counties".
  /// @param[out]   table An Table instance for the opened table.
  /// @return       A long integer indicating whether the method finished successfully.
  long OpenTable(const std::wstring& path, Table& table);

  /// Closes a table that has been previously created or opened.
  /// @param[in]    table The table to close.
  /// @return       A long integer indicating whether the method finished successfully.
  long CloseTable(Table& table);

  /// Renames a dataset.
  /// @param[in]    path The path of the dataset, e.g. "\Landbase\Parcels".
  /// @param[in]    newName The name to apply to the dataset, e.g. "Parcels2".
  /// @return       A long integer indicating whether the method finished successfully.
  long Rename(const std::wstring& path, const std::wstring& newName);

  /// Moves a dataset from one container to another.
  /// @param[in]    path The path of the dataset to move, e.g. "\Landbase\Parcels".
  /// @param[in]    newParentPath The path of the container the dataset will be moved to, e.g. "\LandUse".
  /// @return       A long integer indicating whether the method finished successfully.
  long Move(const std::wstring& path, const std::wstring& newParentPath);

  /// Deletes a dataset.
  /// If a the dataset does not exist, this will fail with an error code of -2147219118 (ROW_NOT_FOUND).<br/>
  /// If you do not have delete access to the dataset, this will fail with an error code of E_FAIL.<br/>
  /// @param[in]    path The path of the dataset to delete, e.g. "\Owners".
  /// @param[in]    datasetType The requested dataset's type as a string, e.g. "Table". <a href="ItemTypes.txt">DatasetType</a>
  /// @return       A long integer indicating whether the method finished successfully.
  long Delete(const std::wstring& path, const std::wstring& datasetType);
  //@}

  /// @name Domains
  //@{
  /// Creates a domain.
  /// If the XML is not UTF-8, create will fail with an error code of -2147024809 (INVALIDARG).<br/>
  /// If the domain name already exists, a -2147215532 (DOMAIN_NAME_ALREADY_EXISTS) error will be returned.<br/>
  /// <a href="CodedValueDomain.xml">XML - Coded Value Domain</a>   <a href="RangeDomain.xml">XML - Range Domain</a>
  /// @param[in]    domainDef The XML definition of the domain to be created.
  /// @return       A long integer indicating whether the method finished successfully.
  long CreateDomain(const std::string& domainDef);

  /// Modifies the properties of an existing domain.
  /// If the XML is not UTF-8, create will fail with an error code of -2147024809 (INVALIDARG).<br/>
  /// @param[in]    domainDef The modified XML definition of the domain.
  /// @return       A long integer indicating whether the method finished successfully.
  long AlterDomain(const std::string& domainDef);

  /// Deletes the specified domain.
  ///If the domain does not exist, this will fail with an error code of -2147209215 (DOMAIN_NOT_FOUND).<br/>
  /// @param[in]    domainName The name of the domain to delete.
  /// @return       A long integer indicating whether the method finished successfully.
  long DeleteDomain(const std::wstring& domainName);

  /// Gets the definition of the specified domain.
  /// @param[in]    domainName The name of the domain.
  /// @param[in]    domainDef The XML definition of the domain to be created.
  /// @return       A long integer indicating whether the method finished successfully.
  long GetDomainDefinition(const std::wstring& domainName, std::string& domainDef);
  //@}

  /// @name SQL
  //@{
  /// Gets the query name (the name to use in SQL statements) of a table based on its path.
  /// @param[in]    path The path of the dataset that will be queried.
  /// @param[out]   queryName The name that should be used for the table in SQL statements.
  /// @return       A long integer indicating whether the method finished successfully.
  long GetQueryName(const std::wstring& path, std::wstring& queryName);

  /// Executes a SQL statement on the geodatabase. This may or may not return a result set.
  /// If the SQL statement is invalid, an -2147220985 (INVALID_SQL) error will be returned.<br/>
  /// @param[in]    sqlStmt The SQL statement to be executed.
  /// @param[in]    recycling Indicates whether the row enumerator should recycle memory.
  /// @param[out]   rows An enumerator of rows or a null value.
  /// @return       A long integer indicating whether the method finished successfully.
  long ExecuteSQL(const std::wstring& sqlStmt, bool recycling, EnumRows& rows);
  //@}

  /// @name Constructors and Destructors
  //@{
  /// The class constructor.
  Geodatabase();

  /// The class destructor.
  ~Geodatabase();
  //@}

private:

  /// @cond PRIVATE
  long CreateGeodatabase(const std::wstring& path);
  long OpenGeodatabase(const std::wstring& path);
  long CloseGeodatabase();
  long DeleteGeodatabase();

  bool IsSetup();

  Catalog* m_pCatalog;

  std::map<Table*, Table*> m_tableROT;

  friend EXT_FILEGDB_API long CreateGeodatabase(const std::wstring& path, Geodatabase& geodatabase);
  friend EXT_FILEGDB_API long OpenGeodatabase(const std::wstring& path, Geodatabase& geodatabase);
  friend EXT_FILEGDB_API long CloseGeodatabase(Geodatabase& geodatabase);
  friend EXT_FILEGDB_API long DeleteGeodatabase(const std::wstring& path);

  friend class Table;

  static std::map<std::wstring, CatalogRef*, ci_less>  m_catalogROT;

  Geodatabase(const Geodatabase&)             { }
  Geodatabase& operator=(const Geodatabase&)  { return *this; }
  /// @endcond
};

};  // namespace FileGDBAPI
