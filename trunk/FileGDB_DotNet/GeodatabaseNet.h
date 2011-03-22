/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#pragma once

#define EXT_FILEGDB_API _declspec(dllimport)
#pragma warning (disable : 4251)

#include "FileGDBAPI.h"

#include "Marshal.h"
#include "TableNet.h"
#include "EnumRowsNet.h"

using namespace std;
using namespace System;
using namespace System::Collections::Generic;
using namespace Runtime::InteropServices;

namespace FileGDB_DotNet 
{
	public ref class GeodatabaseNet
	{
	private:
		FileGDBAPI::Geodatabase* m_geodatabase;

	public:
		GeodatabaseNet() : m_geodatabase(new FileGDBAPI::Geodatabase) {};

		virtual ~GeodatabaseNet() 
		{
			delete this->m_geodatabase;
		}

#pragma region "Geodatabase Management"

		void CreateGeodatabase(String^ path);
		void OpenGeodatabase(String^ path);
		void CloseGeodatabase();
		void DeleteGeodatabase(String^ path);

#pragma endregion


#pragma region "Schema Browsing"

		List<String^>^ GetDatasetTypes();
		List<String^>^ GetDatasetRelationshipTypes();
		List<String^>^ GetChildDatasets(String^ parentPath, String^ datasetType);
		List<String^>^ GetRelatedDatasets(String^ path, String^ relType, String^ datasetType);

#pragma endregion


#pragma region "Schema Definition"

		String^ GetDatasetDefinition(String^ path, String^ datasetType);
		List<String^>^ GetChildDatasetDefinitions(String^ parentPath, String^ datasetType);
		List<String^>^ GetRelatedDatasetDefinitions(String^ path, String^ relType, String^ datasetType);
		String^ GetDatasetDocumentation(String^ path, String^ datasetType);

#pragma endregion


#pragma region "Datasets"
		void CreateFeatureDataset(String^ datasetDef);
		FileGDB_DotNet::TableNet^ CreateTable(String^ tableDef, String^ parent);
		FileGDB_DotNet::TableNet^ OpenTable(String^ path);
		void CloseTable(FileGDB_DotNet::TableNet^ table);
		void Rename(String^ path, String^ datasetType, String^ newName);
		void Move(String^ path, String^ newParentPath);
		void Delete(String^ path, String^ datasetType);
#pragma endregion


#pragma region "Domains"

		void CreateDomain(String^ domainDef);
		void AlterDomain(String^ domainDef);
		void DeleteDomain(String^ domainName);
		String^ GetDomainDefinition(String^ domainName);


#pragma endregion


#pragma region "SQL"

		String^ GetQueryName(String^ path);
		FileGDB_DotNet::EnumRowsNet^ ExecuteSQL(String^ sqlStmt, bool recycling);

#pragma endregion

	protected:
		!GeodatabaseNet() {
			delete this->m_geodatabase;
		}
	};
}
