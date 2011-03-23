/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#pragma once

#define EXT_FILEGDB_API _declspec(dllimport)
#pragma warning (disable : 4251)

#include "FileGDBAPI.h"
#include "ConstantsNet.h"

using namespace std;
using namespace System;
using namespace Runtime::InteropServices;

namespace FileGDB_DotNet 
{
	public ref class FieldInfoNet
	{
	public:
		FieldInfoNet() : fgdbApiFieldInfo(new FileGDBAPI::FieldInfo) {};

		virtual ~FieldInfoNet() 
		{
			delete this->fgdbApiFieldInfo;
		}

		FileGDBAPI::FieldInfo* fgdbApiFieldInfo;

		int GetFieldCount();
		String^ GetFieldName(int fieldNumber);
		FieldTypeNet GetFieldType(int fieldNumber);
		int GetFieldLength(int fieldNumber);
		bool GetFieldIsNullable(int fieldNumber);

	protected:
		!FieldInfoNet() {
			delete this->fgdbApiFieldInfo;
		}
	};
}