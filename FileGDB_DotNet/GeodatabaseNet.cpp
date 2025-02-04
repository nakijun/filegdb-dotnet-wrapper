/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


// This is the main DLL file.

#include "stdafx.h"

#include "GeodatabaseNet.h"
#include "FGDBException.h"

using namespace std;

namespace FileGDB_DotNet 
{
#pragma region "Geodatabase Management Methods"
	void GeodatabaseNet::CreateGeodatabase(String^ path)
	{
		std::wstring wPath;
		MarshalString(path, wPath);

		fgdbError hr;
		if ((hr = FileGDBAPI::CreateGeodatabase(wPath, *this->m_geodatabase)) != S_OK) {
			throw gcnew FGDBException("Error creating geodatabase.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	void GeodatabaseNet::OpenGeodatabase(String^ path)
	{
		std::wstring wPath;
		MarshalString(path, wPath);

		fgdbError hr;
		if ((hr = FileGDBAPI::OpenGeodatabase(wPath, *this->m_geodatabase)) != S_OK) {
			throw gcnew FGDBException("Error opening geodatabase.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	void GeodatabaseNet::CloseGeodatabase()
	{
		fgdbError hr = FileGDBAPI::CloseGeodatabase(*this->m_geodatabase);
	}

	void GeodatabaseNet::DeleteGeodatabase(String^ path)
	{
		std::wstring wPath;
		MarshalString(path, wPath);

		fgdbError hr;
		if ((hr = FileGDBAPI::DeleteGeodatabase(wPath)) != S_OK) {
			throw gcnew FGDBException("Error deleting geodatabase.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")", hr);
		}
	}
#pragma endregion

#pragma region "Schema Browsing"

	List<String^>^ GeodatabaseNet::GetDatasetTypes()
	{
		std::vector<std::wstring> datasetTypes;
		
		fgdbError hr;
		if ((hr = this->m_geodatabase->GetDatasetTypes(datasetTypes)) != S_OK) {
			throw gcnew Exception("Error getting dataset types.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")");
		}

		return MarshalVector(datasetTypes);
	}

	List<String^>^ GeodatabaseNet::GetDatasetRelationshipTypes()
	{
		std::vector<std::wstring> datasetRelTypes;
		
		fgdbError hr;
		if ((hr = this->m_geodatabase->GetDatasetRelationshipTypes(datasetRelTypes)) != S_OK) {
			throw gcnew Exception("Error getting dataset relationship types.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")");
		}

		return MarshalVector(datasetRelTypes);
	}

	List<String^>^ GeodatabaseNet::GetChildDatasets(String^ parentPath, String^ datasetType)
	{
		std::wstring wParentPath, wDatasetType;
		MarshalString(parentPath, wParentPath);
		MarshalString(datasetType, wDatasetType);

		std::vector<std::wstring> childDatasets;
		
		fgdbError hr;
		if ((hr = this->m_geodatabase->GetChildDatasets(wParentPath, wDatasetType, childDatasets)) != S_OK) {
			throw gcnew Exception("Error getting child datasets.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")");
		}

		return MarshalVector(childDatasets);
	}

	List<String^>^ GeodatabaseNet::GetRelatedDatasets(String^ path, String^ relType, String^ datasetType)
	{
		std::wstring wPath, wRelType, wDatasetType;
		MarshalString(path, wPath);
		MarshalString(relType, wRelType);
		MarshalString(datasetType, wDatasetType);

		std::vector<std::wstring> relDatasets;		
		fgdbError hr;
		if ((hr = this->m_geodatabase->GetRelatedDatasets(wPath, wRelType, wDatasetType, relDatasets)) != S_OK) {
			throw gcnew Exception("Error getting related datasets.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")");
		}

		return MarshalVector(relDatasets);
	}

#pragma endregion


#pragma region "Schema Definition"

	String^ GeodatabaseNet::GetDatasetDefinition(String^ path, String^ datasetType) 
	{
		std::wstring wPath, wDatasetType;
		MarshalString(path, wPath);
		MarshalString(datasetType, wDatasetType);

		std::string datasetDef;
		fgdbError hr;
		if ((hr = this->m_geodatabase->GetDatasetDefinition(wPath, wDatasetType, datasetDef)) != S_OK) {
			throw gcnew Exception("Error getting dataset definition.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")");
		}

		String^ sDatasetDef = gcnew String(datasetDef.c_str());
		return sDatasetDef;
	}

	List<String^>^ GeodatabaseNet::GetChildDatasetDefinitions(String^ parentPath, String^ datasetType)
	{
		std::wstring wParentPath, wDatasetType;
		MarshalString(parentPath, wParentPath);
		MarshalString(datasetType, wDatasetType);

		std::vector<std::string> relChildDatasetDefs;		
		fgdbError hr;
		if ((hr = this->m_geodatabase->GetChildDatasetDefinitions(wParentPath, wDatasetType, relChildDatasetDefs)) != S_OK) {
			throw gcnew Exception("Error getting child datasets definitions.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")");
		}

		return MarshalVector(relChildDatasetDefs);
	}

	List<String^>^ GeodatabaseNet::GetRelatedDatasetDefinitions(String^ path, String^ relType, String^ datasetType)
	{
		std::wstring wPath, wRelType, wDatasetType;
		MarshalString(path, wPath);
		MarshalString(relType, wRelType);
		MarshalString(datasetType, wDatasetType);

		std::vector<std::string> relDatasetDefs;		
		fgdbError hr;
		if ((hr = this->m_geodatabase->GetRelatedDatasetDefinitions(wPath, wRelType, wDatasetType, relDatasetDefs)) != S_OK) {
			throw gcnew Exception("Error getting related dataset definitions.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")");
		}

		return MarshalVector(relDatasetDefs);
	}

	String^ GeodatabaseNet::GetDatasetDocumentation(String^ path, String^ datasetType) 
	{
		std::wstring wPath, wDatasetType;
		MarshalString(path, wPath);
		MarshalString(datasetType, wDatasetType);

		std::string datasetDoc;
		fgdbError hr;
		if ((hr = this->m_geodatabase->GetDatasetDocumentation(wPath, wDatasetType, datasetDoc)) != S_OK) {
			throw gcnew Exception("Error getting dataset documentation.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")");
		}

		String^ sDatasetDoc = gcnew String(datasetDoc.c_str());
		return sDatasetDoc;
	}

#pragma endregion

#pragma region "Datasets"

	void GeodatabaseNet::CreateFeatureDataset(String^ datasetDef) 
	{
		std::string sDatasetDef;
		MarshalString(datasetDef, sDatasetDef);

		fgdbError hr;
		if ((hr = this->m_geodatabase->CreateFeatureDataset(sDatasetDef)) != S_OK) {
			throw gcnew FGDBException("Error creating feature dataset.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	TableNet^ GeodatabaseNet::CreateTable(String^ tableDef, String^ parent) 
	{
		std::string sTableDef;
		std::wstring wParent;
		MarshalString(tableDef, sTableDef);
		MarshalString(parent, wParent);

		fgdbError hr;
		TableNet^ table = gcnew TableNet();
		if ((hr = this->m_geodatabase->CreateTable(sTableDef, wParent, *table->fgdbApiTable)) != S_OK) 
		{
			delete table;
			throw gcnew Exception("Error creating table.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")");
		}

		return table;
	}

	TableNet^ GeodatabaseNet::OpenTable(String^ path) 
	{
		std::wstring wPath;
		MarshalString(path, wPath);

		fgdbError hr;
		TableNet^ table = gcnew TableNet();
		if ((hr = this->m_geodatabase->OpenTable(wPath, *table->fgdbApiTable)) != S_OK) {
			delete table;
			throw gcnew Exception("Error opening table.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")");
		}

		return table;
	}

	void GeodatabaseNet::CloseTable(TableNet^ table) 
	{
		fgdbError hr;
		if ((hr = this->m_geodatabase->CloseTable(*table->fgdbApiTable)) != S_OK) {
			throw gcnew FGDBException("Error closing table.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	void GeodatabaseNet::Rename(String^ path, String^ datasetType, String^ newName) 
	{
		std::wstring wPath, wDatasetType, wNewName;
		MarshalString(path, wPath);
		MarshalString(datasetType, wDatasetType);
		MarshalString(newName, wNewName);

		fgdbError hr;
		if ((hr = this->m_geodatabase->Rename(wPath, wDatasetType, wNewName)) != S_OK) {
			throw gcnew FGDBException("Error renaming table.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	void GeodatabaseNet::Move(String^ path, String^ newParentPath) 
	{
		std::wstring wPath, wNewParentPath;
		MarshalString(path, wPath);
		MarshalString(newParentPath, wNewParentPath);

		fgdbError hr;
		if ((hr = this->m_geodatabase->Move(wPath, wNewParentPath)) != S_OK) {
			throw gcnew FGDBException("Error moving table.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	void GeodatabaseNet::Delete(String^ path, String^ datasetType) 
	{
		std::wstring wPath, wDatasetType;
		MarshalString(path, wPath);
		MarshalString(datasetType, wDatasetType);

		fgdbError hr;
		if ((hr = this->m_geodatabase->Delete(wPath, wDatasetType)) != S_OK) {
			throw gcnew FGDBException("Error deleting table.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")", hr);
		}
	}

#pragma endregion


#pragma region "Domains"

	void GeodatabaseNet::CreateDomain(String^ domainDef) 
	{
		std::string sDomainDef;
		MarshalString(domainDef, sDomainDef);

		fgdbError hr;
		if ((hr = this->m_geodatabase->CreateDomain(sDomainDef)) != S_OK) {
			throw gcnew FGDBException("Error creating domain.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	void GeodatabaseNet::AlterDomain(String^ domainDef) 
	{
		std::string sDomainDef;
		MarshalString(domainDef, sDomainDef);

		fgdbError hr;
		if ((hr = m_geodatabase->AlterDomain(sDomainDef)) != S_OK) {
			throw gcnew FGDBException("Error altering domain.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	void GeodatabaseNet::DeleteDomain(String^ domainName) 
	{
		std::wstring wDomainName;
		MarshalString(domainName, wDomainName);

		fgdbError hr;
		if ((hr = this->m_geodatabase->DeleteDomain(wDomainName)) != S_OK) {
			throw gcnew FGDBException("Error deleting domain.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	String^ GeodatabaseNet::GetDomainDefinition(String^ domainName) 
	{
		std::wstring wDomainName;
		MarshalString(domainName, wDomainName);

		std::string domainDef;
		fgdbError hr;
		if ((hr = this->m_geodatabase->GetDomainDefinition(wDomainName, domainDef)) != S_OK) {
			throw gcnew Exception("Error getting domain definition.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")");
		}

		String^ sDomainDef = gcnew String(domainDef.c_str());
		return sDomainDef;
	}

#pragma endregion


#pragma region "SQL"

	String^ GeodatabaseNet::GetQueryName(String^ path) 
	{
		std::wstring wPath;
		MarshalString(path, wPath);

		std::wstring queryName;
		fgdbError hr;
		if ((hr = this->m_geodatabase->GetQueryName(wPath, queryName)) != S_OK) {
			throw gcnew Exception("Error getting query name.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")");
		}

		String^ sQueryName = gcnew String(queryName.c_str());
		return sQueryName;
	}

	FileGDB_DotNet::EnumRowsNet^ GeodatabaseNet::ExecuteSQL(String^ sqlStmt, bool recycling) 
	{
		std::wstring wSqlStmt;
		MarshalString(sqlStmt, wSqlStmt);

		fgdbError hr;
		FileGDB_DotNet::EnumRowsNet^ enumRow = gcnew FileGDB_DotNet::EnumRowsNet();
		if ((hr = this->m_geodatabase->ExecuteSQL(wSqlStmt, recycling, *enumRow->fgdbApiEnumRows)) != S_OK) 
		{
			delete enumRow;
			throw gcnew Exception("Error executing sql statement.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")");
		}

		return enumRow;
	}

#pragma endregion

}