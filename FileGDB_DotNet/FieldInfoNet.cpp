/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#include "stdafx.h"

#include "FGDBException.h"
#include "FieldInfoNet.h"

namespace FileGDB_DotNet 
{
	int FieldInfoNet::GetFieldCount()
	{
		int fieldCount;
		fgdbError hr;
		if ((hr = this->fgdbApiFieldInfo->GetFieldCount(fieldCount)) != S_OK) {
			throw gcnew FGDBException("Error getting field count.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return fieldCount;
	}

	String^ FieldInfoNet::GetFieldName(int fieldNumber)
	{
		std::wstring fieldName;
		fgdbError hr;
		if ((hr = this->fgdbApiFieldInfo->GetFieldName(fieldNumber, fieldName)) != S_OK) {
			throw gcnew FGDBException("Error getting field name.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return gcnew String(fieldName.c_str());
	}

	FieldTypeNet FieldInfoNet::GetFieldType(int fieldNumber)
	{
		FileGDBAPI::FieldType fieldType;		
		fgdbError hr;
		if ((hr = this->fgdbApiFieldInfo->GetFieldType(fieldNumber, fieldType)) != S_OK) {
			throw gcnew FGDBException("Error getting field type.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return (FieldTypeNet)((int)fieldType);
	}

	int FieldInfoNet::GetFieldLength(int fieldNumber)
	{
		int fieldLength;
		fgdbError hr;
		if ((hr = this->fgdbApiFieldInfo->GetFieldLength(fieldNumber, fieldLength)) != S_OK) {
			throw gcnew FGDBException("Error getting field length.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return fieldLength;
	}

	bool FieldInfoNet::GetFieldIsNullable(int fieldNumber)
	{
		bool isNullable;
		fgdbError hr;
		if ((hr = this->fgdbApiFieldInfo->GetFieldIsNullable(fieldNumber, isNullable)) != S_OK) {
			throw gcnew FGDBException("Error getting is field nullable value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return isNullable;
	}
}