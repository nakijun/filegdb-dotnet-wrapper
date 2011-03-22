/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#pragma once

#include "FileGDBAPI.h"

using namespace System;

namespace FileGDB_DotNet 
{
	public ref class FGDBException : System::Exception
	{
	private:
		fgdbError m_errorCode;
		String^ m_errorDescription;

	public:
		FGDBException(System::String^ message, fgdbError hr) : System::Exception(message)
		{
			this->m_errorCode = hr;

			std::wstring errorDescription;
			if (FileGDBAPI::ErrorInfo::GetErrorDescription(hr, errorDescription) == S_OK)
				m_errorDescription = gcnew String(errorDescription.c_str());
			else
				m_errorDescription = "";

		}

		property long ErrorCode
		{
			long get() { return this->m_errorCode; }
		}

		property String^ ErrorDescription
		{
			String^ get() { return this->m_errorDescription; }
		}
	};
}