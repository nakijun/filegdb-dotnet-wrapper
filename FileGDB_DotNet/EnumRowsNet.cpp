/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#include "stdafx.h"

#include "EnumRowsNet.h"
#include "FGDBException.h"

namespace FileGDB_DotNet 
{
	FileGDB_DotNet::RowNet^ EnumRowsNet::Next() 
	{
		RowNet^ netrow = gcnew RowNet();
		fgdbError hr;
		if ((hr = this->fgdbApiEnumRows->Next(*netrow->fgdbApiRow)) != S_OK) {
			if (hr == 1)
				return nullptr;
			else
				throw gcnew FGDBException("Error getting next row.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return netrow;
	}

	void EnumRowsNet::Close()
	{
		this->fgdbApiEnumRows->Close();
	}
}