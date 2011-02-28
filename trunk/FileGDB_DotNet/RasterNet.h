#pragma once

#define EXT_FILEGDB_API _declspec(dllimport)
#pragma warning (disable : 4251)

#include "FileGDB_API_1_0_beta2/include/FileGDBAPI.h"

using namespace std;
using namespace System;
using namespace Runtime::InteropServices;

namespace FileGDB_DotNet 
{
	public ref class RasterNet
	{
	public:
		RasterNet() : fgdbApiRaster(new FileGDBAPI::Raster) {};

		~RasterNet() 
		{
			delete fgdbApiRaster;
		}

		FileGDBAPI::Raster* fgdbApiRaster;

	protected:
		!RasterNet() {
			delete fgdbApiRaster;
		}
	};
}