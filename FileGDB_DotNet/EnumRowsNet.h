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

		void Next(FileGDB_DotNet::RowNet^ row);
		void Close();

	protected:
		!EnumRowsNet() {
			delete fgdbApiEnumRows;
		}
	};
}