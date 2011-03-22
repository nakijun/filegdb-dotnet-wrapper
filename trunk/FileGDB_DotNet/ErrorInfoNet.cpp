/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */

#include "stdafx.h"
#include "FGDBException.h"
#include "FileGDBAPI.h"

using namespace System;
using namespace Runtime::InteropServices;

namespace FileGDB_DotNet
{
	namespace ErrorInfo
	{
		/// Returns the text error message which corresponds to an error code.
		/// If there is no description corresponding to the error code, the error
		/// description string will be empty and a 1 (S_FALSE) error will be returned.
		/// @param[in]    fgdbError The error code to look up.
		/// @param[out]   errorDescription The description of the error.
		/// @return       Error code indicating whether the method finished successfully.
		String^ GetErrorDescription(fgdbError error)
		{
			std::wstring errorDescription;
			fgdbError hr = FileGDBAPI::ErrorInfo::GetErrorDescription(error, errorDescription);
			if (hr == S_OK)
				return gcnew String(errorDescription.c_str());
			else if (hr == S_FALSE)
				return "No error description found";
			else
				throw gcnew FGDBException("Error getting error description.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		/// Returns the number of error records in the error stack.
		/// @param[out]   recordCount The number of error records.
		/// @return       Void.
		int GetErrorRecordCount()
		{
			int recordCount;
			FileGDBAPI::ErrorInfo::GetErrorRecordCount(recordCount);
			return recordCount;
		}

		/// Returns an error record.
		/// @param[in]    recordNum The error record to return.
		/// @param[out]   fgdbError The error code.
		/// @param[out]   errorDescription The description of the error.
		/// @return       Error code indicating whether the method finished successfully.
		void GetErrorRecord(int recordNum, [Out] fgdbError error, [Out] String^ errorDescription)
		{
			fgdbError hr;
			std::wstring wErrorDescription;
			if ((hr = FileGDBAPI::ErrorInfo::GetErrorRecord(recordNum, error, wErrorDescription)) != S_OK) {
				throw gcnew FGDBException("Error getting error record.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
			}
		}

		/// Clears the error stack.
		/// @return       Void.
		void ClearErrors(void)
		{
			FileGDBAPI::ErrorInfo::ClearErrors();
		}
	}
}