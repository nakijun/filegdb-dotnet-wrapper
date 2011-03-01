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

		long hr;
		if ((hr = FileGDBAPI::CreateGeodatabase(wPath, *m_geodatabase)) != S_OK) {
			throw gcnew FGDBException("Error creating geodatabase.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	void GeodatabaseNet::OpenGeodatabase(String^ path)
	{
		std::wstring wPath;
		MarshalString(path, wPath);

		long hr;
		if ((hr = FileGDBAPI::OpenGeodatabase(wPath, *m_geodatabase)) != S_OK) {
			throw gcnew FGDBException("Error opening geodatabase.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	void GeodatabaseNet::CloseGeodatabase()
	{
		long hr = FileGDBAPI::CloseGeodatabase(*m_geodatabase);
	}

	void GeodatabaseNet::DeleteGeodatabase(String^ path)
	{
		std::wstring wPath;
		MarshalString(path, wPath);

		long hr;
		if ((hr = FileGDBAPI::DeleteGeodatabase(wPath)) != S_OK) {
			throw gcnew FGDBException("Error deleting geodatabase.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")", hr);
		}
	}
#pragma endregion

#pragma region "Schema Browsing"

	List<String^>^ GeodatabaseNet::GetDatasetTypes()
	{
		std::vector<std::wstring> datasetTypes;
		
		long hr;
		if ((hr = m_geodatabase->GetDatasetTypes(datasetTypes)) != S_OK) {
			throw gcnew Exception("Error getting dataset types.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")");
		}

		List<String^>^ lDatasetTypes;
		MarshalVector(datasetTypes, lDatasetTypes);
		return lDatasetTypes;
	}

	List<String^>^ GeodatabaseNet::GetDatasetRelationshipTypes()
	{
		std::vector<std::wstring> datasetRelTypes;
		
		long hr;
		if ((hr = m_geodatabase->GetDatasetRelationshipTypes(datasetRelTypes)) != S_OK) {
			throw gcnew Exception("Error getting dataset relationship types.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")");
		}

		List<String^>^ lDatasetRelTypes;
		MarshalVector(datasetRelTypes, lDatasetRelTypes);
		return lDatasetRelTypes;
	}

	List<String^>^ GeodatabaseNet::GetChildDatasets(String^ parentPath, String^ datasetType)
	{
		std::wstring wParentPath, wDatasetType;
		MarshalString(parentPath, wParentPath);
		MarshalString(datasetType, wDatasetType);

		std::vector<std::wstring> childDatasets;
		
		long hr;
		if ((hr = m_geodatabase->GetChildDatasets(wParentPath, wDatasetType, childDatasets)) != S_OK) {
			throw gcnew Exception("Error getting child datasets.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")");
		}

		List<String^>^ lChildDatasets;
		MarshalVector(childDatasets, lChildDatasets);
		return lChildDatasets;
	}

	List<String^>^ GeodatabaseNet::GetRelatedDatasets(String^ path, String^ relType, String^ datasetType)
	{
		std::wstring wPath, wRelType, wDatasetType;
		MarshalString(path, wPath);
		MarshalString(relType, wRelType);
		MarshalString(datasetType, wDatasetType);

		std::vector<std::wstring> relDatasets;		
		long hr;
		if ((hr = m_geodatabase->GetRelatedDatasets(wPath, wRelType, wDatasetType, relDatasets)) != S_OK) {
			throw gcnew Exception("Error getting related datasets.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")");
		}

		List<String^>^ lRelDatasets;
		MarshalVector(relDatasets, lRelDatasets);
		return lRelDatasets;
	}

#pragma endregion


#pragma region "Schema Definition"

	String^ GeodatabaseNet::GetDatasetDefinition(String^ path, String^ datasetType) 
	{
		std::wstring wPath, wDatasetType;
		MarshalString(path, wPath);
		MarshalString(datasetType, wDatasetType);

		std::string datasetDef;
		long hr;
		if ((hr = m_geodatabase->GetDatasetDefinition(wPath, wDatasetType, datasetDef)) != S_OK) {
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
		long hr;
		if ((hr = m_geodatabase->GetChildDatasetDefinitions(wParentPath, wDatasetType, relChildDatasetDefs)) != S_OK) {
			throw gcnew Exception("Error getting child datasets definitions.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")");
		}

		List<String^>^ lRelChildDatasetDefs;
		MarshalVector(relChildDatasetDefs, lRelChildDatasetDefs);
		return lRelChildDatasetDefs;
	}

	List<String^>^ GeodatabaseNet::GetRelatedDatasetDefinitions(String^ path, String^ relType, String^ datasetType)
	{
		std::wstring wPath, wRelType, wDatasetType;
		MarshalString(path, wPath);
		MarshalString(relType, wRelType);
		MarshalString(datasetType, wDatasetType);

		std::vector<std::string> relDatasetDefs;		
		long hr;
		if ((hr = m_geodatabase->GetRelatedDatasetDefinitions(wPath, wRelType, wDatasetType, relDatasetDefs)) != S_OK) {
			throw gcnew Exception("Error getting related dataset definitions.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")");
		}

		List<String^>^ lRelDatasetDefs;
		MarshalVector(relDatasetDefs, lRelDatasetDefs);
		return lRelDatasetDefs;
	}

	String^ GeodatabaseNet::GetDatasetDocumentation(String^ path, String^ datasetType) 
	{
		std::wstring wPath, wDatasetType;
		MarshalString(path, wPath);
		MarshalString(datasetType, wDatasetType);

		std::string datasetDoc;
		long hr;
		if ((hr = m_geodatabase->GetDatasetDocumentation(wPath, wDatasetType, datasetDoc)) != S_OK) {
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

		long hr;
		if ((hr = m_geodatabase->CreateFeatureDataset(sDatasetDef)) != S_OK) {
			throw gcnew FGDBException("Error creating feature dataset.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	TableNet^ GeodatabaseNet::CreateTable(String^ tableDef, String^ parent) 
	{
		std::string sTableDef;
		std::wstring wParent;
		MarshalString(tableDef, sTableDef);
		MarshalString(parent, wParent);

		long hr;
		TableNet^ table = gcnew TableNet();
		if ((hr = m_geodatabase->CreateTable(sTableDef, wParent, *table->fgdbApiTable)) != S_OK) 
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

		long hr;
		TableNet^ table = gcnew TableNet();
		if ((hr = m_geodatabase->OpenTable(wPath, *table->fgdbApiTable)) != S_OK) {
			delete table;
			throw gcnew Exception("Error opening table.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")");
		}

		return table;
	}

	void GeodatabaseNet::CloseTable(TableNet^ table) 
	{
		long hr;
		if ((hr = m_geodatabase->CloseTable(*table->fgdbApiTable)) != S_OK) {
			throw gcnew FGDBException("Error closing table.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	void GeodatabaseNet::Rename(String^ path, String^ newName) 
	{
		std::wstring wPath, wNewName;
		MarshalString(path, wPath);
		MarshalString(newName, wNewName);

		long hr;
		if ((hr = m_geodatabase->Rename(wPath, wNewName)) != S_OK) {
			throw gcnew FGDBException("Error renaming table.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	void GeodatabaseNet::Move(String^ path, String^ newParentPath) 
	{
		std::wstring wPath, wNewParentPath;
		MarshalString(path, wPath);
		MarshalString(newParentPath, wNewParentPath);

		long hr;
		if ((hr = m_geodatabase->Move(wPath, wNewParentPath)) != S_OK) {
			throw gcnew FGDBException("Error moving table.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	void GeodatabaseNet::Delete(String^ path, String^ datasetType) 
	{
		std::wstring wPath, wDatasetType;
		MarshalString(path, wPath);
		MarshalString(datasetType, wDatasetType);

		long hr;
		if ((hr = m_geodatabase->Delete(wPath, wDatasetType)) != S_OK) {
			throw gcnew FGDBException("Error deleting table.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")", hr);
		}
	}

#pragma endregion


#pragma region "Domains"

	void GeodatabaseNet::CreateDomain(String^ domainDef) 
	{
		std::string sDomainDef;
		MarshalString(domainDef, sDomainDef);

		long hr;
		if ((hr = m_geodatabase->CreateDomain(sDomainDef)) != S_OK) {
			throw gcnew FGDBException("Error creating domain.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	void GeodatabaseNet::AlterDomain(String^ domainDef) 
	{
		std::string sDomainDef;
		MarshalString(domainDef, sDomainDef);

		long hr;
		if ((hr = m_geodatabase->AlterDomain(sDomainDef)) != S_OK) {
			throw gcnew FGDBException("Error altering domain.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	void GeodatabaseNet::DeleteDomain(String^ domainName) 
	{
		std::wstring wDomainName;
		MarshalString(domainName, wDomainName);

		long hr;
		if ((hr = m_geodatabase->DeleteDomain(wDomainName)) != S_OK) {
			throw gcnew FGDBException("Error deleting domain.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	String^ GeodatabaseNet::GetDomainDefinition(String^ domainName) 
	{
		std::wstring wDomainName;
		MarshalString(domainName, wDomainName);

		std::string domainDef;
		long hr;
		if ((hr = m_geodatabase->GetDomainDefinition(wDomainName, domainDef)) != S_OK) {
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
		long hr;
		if ((hr = m_geodatabase->GetQueryName(wPath, queryName)) != S_OK) {
			throw gcnew Exception("Error getting query name.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")");
		}

		String^ sQueryName = gcnew String(queryName.c_str());
		return sQueryName;
	}

	FileGDB_DotNet::EnumRowsNet^ GeodatabaseNet::ExecuteSQL(String^ sqlStmt, bool recycling) 
	{
		std::wstring wSqlStmt;
		MarshalString(sqlStmt, wSqlStmt);

		long hr;
		FileGDB_DotNet::EnumRowsNet^ enumRow = gcnew FileGDB_DotNet::EnumRowsNet();
		if ((hr = m_geodatabase->ExecuteSQL(wSqlStmt, recycling, *enumRow->fgdbApiEnumRows)) != S_OK) 
		{
			delete enumRow;
			throw gcnew Exception("Error executing sql statement.  Error code: " + hr + " (0x" + hr.ToString("X8") + ")");
		}

		return enumRow;
	}

#pragma endregion

}