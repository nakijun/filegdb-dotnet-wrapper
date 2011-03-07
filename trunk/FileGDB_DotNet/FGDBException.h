/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#pragma once

namespace FileGDB_DotNet 
{
	public ref class FGDBException : System::Exception
	{
	private:
		long m_errorCode;
	public:
		FGDBException(System::String^ message, long hr) : System::Exception(message)
		{
			this->m_errorCode = hr;
		}

		property long ErrorCode
		{
			long get() { return this->m_errorCode; }
		}
	};
}