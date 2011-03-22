/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#pragma once

#define EXT_FILEGDB_API _declspec(dllimport)
#pragma warning (disable : 4251)

#include "FileGDBAPI.h"

#include "EnumRowsNet.h"
#include "EnvelopeNet.h"

using namespace std;
using namespace System;
using namespace System::Collections::Generic;
using namespace Runtime::InteropServices;

namespace FileGDB_DotNet 
{
	public ref class TableNet
	{
	public:
		TableNet() : fgdbApiTable(new FileGDBAPI::Table) {};

		virtual ~TableNet() 
		{
			delete this->fgdbApiTable;
		}

		FileGDBAPI::Table* fgdbApiTable;

#pragma region "Schema"

		String^ GetDefinition();
		String^ GetDocumentation();
		void SetDocumentation(String^ documentation);
		void AddField(String^ fieldDef);
		void AlterField(String^ fieldDef);
		void DeleteField(String^ fieldName);
		List<String^>^ GetIndexes();
		void AddIndex(String^ indexDef);
		void DeleteIndex(String^ indexName);
		void CreateSubtype(String^ subtypeDef);
		void AlterSubtype(String^ subtypeDef);
		void DeleteSubtype(String^ subtypeName);
		void EnableSubtypes(String^ subtypeFieldName, String^ subtypeDef);
		int GetDefaultSubtypeCode();
		void SetDefaultSubtypeCode(int defaultCode);
		void DisableSubtypes();

#pragma endregion

#pragma region "Data"

		EnumRowsNet^ Search(String^ subfields, String^ whereClause, EnvelopeNet^ envelope, bool recycling);
		EnumRowsNet^ Search(String^ subfields, String^ whereClause, bool recycling);
		RowNet^ CreateRowObject();
		void Insert(RowNet^ row);
		void Update(RowNet^ row);
		void Delete(RowNet^ row);
		bool IsEditable();
		long GetRowCount();
		EnvelopeNet^ GetExtent();

#pragma endregion

	protected:
		!TableNet() {
			delete this->fgdbApiTable;
		}
	};
}