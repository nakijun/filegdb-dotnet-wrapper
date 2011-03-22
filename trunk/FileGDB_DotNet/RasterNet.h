/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#pragma once

#define EXT_FILEGDB_API _declspec(dllimport)
#pragma warning (disable : 4251)

#include "FileGDBAPI.h"

using namespace std;
using namespace System;
using namespace Runtime::InteropServices;

namespace FileGDB_DotNet 
{
	public ref class RasterNet
	{
	public:
		RasterNet() : fgdbApiRaster(new FileGDBAPI::Raster) {};

		virtual ~RasterNet() 
		{
			delete this->fgdbApiRaster;
		}

		FileGDBAPI::Raster* fgdbApiRaster;

	protected:
		!RasterNet() {
			delete this->fgdbApiRaster;
		}
	};
}