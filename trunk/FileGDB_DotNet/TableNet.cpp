// This is the main DLL file.

#include "stdafx.h"

#include "TableNet.h"
#include "FGDBException.h"
#include "Marshal.h"

namespace FileGDB_DotNet 
{
	String^ TableNet::GetDefinition()
	{
		std::string definition;
		long hr;
		if ((hr = fgdbApiTable->GetDefinition(definition)) != S_OK) {
			throw gcnew FGDBException("Error getting table definition.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return gcnew String(definition.c_str());
	}

	String^ TableNet::GetDocumentation()
	{
		std::string documentation;
		long hr;
		if ((hr = fgdbApiTable->GetDocumentation(documentation)) != S_OK) {
			throw gcnew FGDBException("Error getting table documentation.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return gcnew String(documentation.c_str());
	}

	void TableNet::SetDocumentation(String^ documentation)
	{
		std::string sDocumentation;
		MarshalString(documentation, sDocumentation);

		long hr;
		if ((hr = fgdbApiTable->SetDocumentation(sDocumentation)) != S_OK) {
			throw gcnew FGDBException("Error setting table documentation.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	void TableNet::AddField(String^ fieldDef)
	{
		std::string sFieldDef;
		MarshalString(fieldDef, sFieldDef);

		long hr;
		if ((hr = fgdbApiTable->AddField(sFieldDef)) != S_OK) {
			throw gcnew FGDBException("Error adding field.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	void TableNet::AlterField(String^ fieldDef)
	{
		std::string sFieldDef;
		MarshalString(fieldDef, sFieldDef);

		long hr;
		if ((hr = fgdbApiTable->AlterField(sFieldDef)) != S_OK) {
			throw gcnew FGDBException("Error altering field.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	void TableNet::DeleteField(String^ fieldName)
	{
		std::wstring wFieldName;
		MarshalString(fieldName, wFieldName);

		long hr;
		if ((hr = fgdbApiTable->DeleteField(wFieldName)) != S_OK) {
			throw gcnew FGDBException("Error deleting field.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	List<String^>^ TableNet::GetIndexes()
	{
		std::vector<std::string> indexDefs;

		long hr;
		if ((hr = fgdbApiTable->GetIndexes(indexDefs)) != S_OK) {
			throw gcnew FGDBException("Error getting indexes.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		List<String^>^ lIndexDefs;
		MarshalVector(indexDefs, lIndexDefs);

		return lIndexDefs;
	}

	void TableNet::AddIndex(String^ indexDef)
	{
		std::string sIndexDef;
		MarshalString(indexDef, sIndexDef);

		long hr;
		if ((hr = fgdbApiTable->AddIndex(sIndexDef)) != S_OK) {
			throw gcnew FGDBException("Error adding index.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	void TableNet::DeleteIndex(String^ indexName)
	{
		std::wstring wIndexName;
		MarshalString(indexName, wIndexName);

		long hr;
		if ((hr = fgdbApiTable->DeleteIndex(wIndexName)) != S_OK) {
			throw gcnew FGDBException("Error deleting index.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	void TableNet::CreateSubtype(String^ subtypeDef)
	{
		std::string sSubtypeDef;
		MarshalString(subtypeDef, sSubtypeDef);

		long hr;
		if ((hr = fgdbApiTable->CreateSubtype(sSubtypeDef)) != S_OK) {
			throw gcnew FGDBException("Error creating subtype.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	void TableNet::AlterSubtype(String^ subtypeDef)
	{
		std::string sSubtypeDef;
		MarshalString(subtypeDef, sSubtypeDef);

		long hr;
		if ((hr = fgdbApiTable->AlterSubtype(sSubtypeDef)) != S_OK) {
			throw gcnew FGDBException("Error altering subtype.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	void TableNet::DeleteSubtype(String^ subtypeName)
	{
		std::wstring wSubtypeName;
		MarshalString(subtypeName, wSubtypeName);

		long hr;
		if ((hr = fgdbApiTable->DeleteSubtype(wSubtypeName)) != S_OK) {
			throw gcnew FGDBException("Error deleting subtype.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	void TableNet::EnableSubtypes(String^ subtypeFieldName, String^ subtypeDef)
	{
		std::wstring wSubtypeFieldName;
		MarshalString(subtypeFieldName, wSubtypeFieldName);
		std::string sSubtypeDef;
		MarshalString(subtypeDef, sSubtypeDef);

		long hr;
		if ((hr = fgdbApiTable->EnableSubtypes(wSubtypeFieldName, sSubtypeDef)) != S_OK) {
			throw gcnew FGDBException("Error enabling subtypes.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	int TableNet::GetDefaultSubtypeCode()
	{
		int defaultCode;
		long hr;
		if ((hr = fgdbApiTable->GetDefaultSubtypeCode(defaultCode)) != S_OK) {
			throw gcnew FGDBException("Error getting default subtype code.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return defaultCode;
	}

	void TableNet::SetDefaultSubtypeCode(int defaultCode)
	{
		long hr;
		if ((hr = fgdbApiTable->SetDefaultSubtypeCode(defaultCode)) != S_OK) {
			throw gcnew FGDBException("Error setting default subtype code.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	void TableNet::DisableSubtypes()
	{
		long hr;
		if ((hr = fgdbApiTable->DisableSubtypes()) != S_OK) {
			throw gcnew FGDBException("Error disabling subtypes.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	EnumRowsNet^ TableNet::Search(String^ subfields, String^ whereClause, EnvelopeNet^ envelope, bool recycling)
	{
		std::wstring wSubfields, wWhereClause;
		MarshalString(subfields, wSubfields);
		MarshalString(whereClause, wWhereClause);

		FileGDBAPI::EnumRows rows;
		long hr;
		if ((hr = fgdbApiTable->Search(wSubfields, wWhereClause, *envelope->fgdbApiEnvelope, recycling, rows)) != S_OK) {
			throw gcnew FGDBException("Error searching table.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		EnumRowsNet^ outrows = gcnew EnumRowsNet();
		outrows->fgdbApiEnumRows = &rows;
		return outrows;
	}

	EnumRowsNet^ TableNet::Search(String^ subfields, String^ whereClause, bool recycling)
	{
		std::wstring wSubfields, wWhereClause;
		MarshalString(subfields, wSubfields);
		MarshalString(whereClause, wWhereClause);

		FileGDBAPI::EnumRows rows;
		long hr;
		if ((hr = fgdbApiTable->Search(wSubfields, wWhereClause, recycling, rows)) != S_OK) {
			throw gcnew FGDBException("Error searching table.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		EnumRowsNet^ outrows = gcnew EnumRowsNet();
		outrows->fgdbApiEnumRows = &rows;
		return outrows;
	}

	RowNet^ TableNet::CreateRowObject()
	{
		FileGDBAPI::Row row;
		long hr;
		if ((hr = fgdbApiTable->CreateRowObject(row)) != S_OK) {
			throw gcnew FGDBException("Error creating row object table.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		RowNet^ outrow = gcnew RowNet();
		outrow->fgdbApiRow = &row;
		return outrow;
	}

	void TableNet::Insert(RowNet^ row)
	{
		long hr;
		if ((hr = fgdbApiTable->Insert(*row->fgdbApiRow)) != S_OK) {
			throw gcnew FGDBException("Error inserting row.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	void TableNet::Update(RowNet^ row)
	{
		long hr;
		if ((hr = fgdbApiTable->Update(*row->fgdbApiRow)) != S_OK) {
			throw gcnew FGDBException("Error updating row.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	void TableNet::Delete(RowNet^ row)
	{
		long hr;
		if ((hr = fgdbApiTable->Delete(*row->fgdbApiRow)) != S_OK) {
			throw gcnew FGDBException("Error deleting row.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	bool TableNet::IsEditable() 
	{
		bool editable;
		long hr;
		if ((hr = fgdbApiTable->IsEditable(editable)) != S_OK) {
			throw gcnew FGDBException("Error getting value for IsEditable.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return editable;
	}

	long TableNet::GetRowCount() 
	{
		long rowCount;
		long hr;
		if ((hr = fgdbApiTable->GetRowCount(rowCount)) != S_OK) {
			throw gcnew FGDBException("Error getting row count.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return rowCount;
	}

	EnvelopeNet^ TableNet::GetExtent()
	{
		FileGDBAPI::Envelope envelope;
		long hr;
		if ((hr = fgdbApiTable->GetExtent(envelope)) != S_OK) {
			throw gcnew FGDBException("Error getting envelope.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		EnvelopeNet^ outenv = gcnew EnvelopeNet();
		outenv->fgdbApiEnvelope = &envelope;
		return outenv;
	}
}