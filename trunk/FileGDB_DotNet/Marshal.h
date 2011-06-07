/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#pragma once

#pragma warning (disable : 4251)

#include "FileGDBAPI.h"

using namespace std;
using namespace System;
using namespace System::Collections::Generic;
using namespace Runtime::InteropServices;

namespace FileGDB_DotNet 
{
	void MarshalString(String^, std::wstring&);
	void MarshalString(String^, std::string&);
	List<String^>^ MarshalVector(std::vector<std::wstring>&);
	List<String^>^ MarshalVector(std::vector<std::string>&);
	System::Guid MarshalGuid(FileGDBAPI::Guid& inguid);
	FileGDBAPI::Guid MarshalGuid(System::Guid& inguid);
	System::DateTime MarshalDateTime(struct tm& indt);
	struct tm MarshalDateTime(System::DateTime& dt);
}