/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#pragma once

#define EXT_FILEGDB_API _declspec(dllimport)
#pragma warning (disable : 4251)

#include "FileGDB_API_1_0_beta2/include/FileGDBAPI.h"
#include "RowNet.h"

namespace FileGDB_DotNet 
{
	public ref class EnumRowsNet
	{
	public:
		EnumRowsNet() : fgdbApiEnumRows(new FileGDBAPI::EnumRows) {};

		~EnumRowsNet() 
		{
			delete fgdbApiEnumRows;
		}

		FileGDBAPI::EnumRows* fgdbApiEnumRows;

		FileGDB_DotNet::RowNet^ Next();
		void Close();

	protected:
		!EnumRowsNet() {
			delete fgdbApiEnumRows;
		}
	};
}