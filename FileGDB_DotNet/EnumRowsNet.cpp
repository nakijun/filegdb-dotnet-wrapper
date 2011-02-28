#include "stdafx.h"

#include "EnumRowsNet.h"
#include "FGDBException.h"

namespace FileGDB_DotNet 
{
	void EnumRowsNet::Next(FileGDB_DotNet::RowNet^ row) 
	{
		FileGDBAPI::Row apiRow;
		long hr;
		if ((hr = fgdbApiEnumRows->Next(apiRow)) != S_OK) {
			throw gcnew FGDBException("Error getting next row.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	void EnumRowsNet::Close()
	{
		fgdbApiEnumRows->Close();
	}
}