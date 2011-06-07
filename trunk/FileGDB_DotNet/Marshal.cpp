/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#include "stdafx.h"

#include "Marshal.h"

namespace FileGDB_DotNet 
{
	void MarshalString(String^ instr, std::wstring& outstr) 
	{
		const wchar_t* chars = (const wchar_t*)(Marshal::StringToHGlobalUni(instr)).ToPointer();
		outstr = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));
	}

	void MarshalString(String^ instr, std::string& outstr) 
	{
	   const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(instr)).ToPointer();
	   outstr = chars;
	   Marshal::FreeHGlobal(IntPtr((void*)chars));
	}

	List<String^>^ MarshalVector(std::vector<std::wstring>& invector) 
	{
		List<String^>^ outlist = gcnew List<String^>();
		vector<std::wstring>::iterator iter = invector.begin();
		while (iter != invector.end()) {
			std::wstring s = *iter;
			outlist->Add(gcnew String(s.c_str()));
			iter++;
		}

		return outlist;
	}

	List<String^>^ MarshalVector(std::vector<std::string>& invector) 
	{
		List<String^>^ outlist = gcnew List<String^>();
		vector<std::string>::iterator iter = invector.begin();
		while (iter != invector.end()) {
			std::string s = *iter;
			outlist->Add(gcnew String(s.c_str()));
			iter++;
		}

		return outlist;
	}

	Guid MarshalGuid(FileGDBAPI::Guid& inguid)
	{
		return Guid(inguid.data1, inguid.data2, inguid.data3,
			inguid.data4[0], inguid.data4[1], inguid.data4[2],
			inguid.data4[3], inguid.data4[4], inguid.data4[5],
			inguid.data4[6], inguid.data4[7]);
	}

	FileGDBAPI::Guid MarshalGuid(System::Guid& inguid)
	{
		array<Byte>^ guidData = inguid.ToByteArray();
		pin_ptr<Byte> data = &(guidData[0]);
		return *(FileGDBAPI::Guid *)data;
	}

	DateTime MarshalDateTime(struct tm& indt)
	{
		return DateTime(1900 + indt.tm_year, 1 + indt.tm_mon, indt.tm_mday,
			indt.tm_hour, indt.tm_min, indt.tm_sec);
	}

	struct tm MarshalDateTime(System::DateTime& indt)
	{
		struct tm outdt = {
			indt.Second,
			indt.Minute,
			indt.Hour,
			indt.Day,
			indt.Month - 1,
			indt.Year - 1900,
			0,
			0,
			-1
		};

		return outdt;
	}
}