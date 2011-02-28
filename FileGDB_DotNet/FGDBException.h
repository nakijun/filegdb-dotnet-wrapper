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
			m_errorCode = hr;
		}

		property long ErrorCode
		{
			long get() { return m_errorCode; }
		}
	};
}