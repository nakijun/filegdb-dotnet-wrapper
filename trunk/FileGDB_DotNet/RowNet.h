#pragma once

#define EXT_FILEGDB_API _declspec(dllimport)
#pragma warning (disable : 4251)

#include "FileGDB_API_1_0_beta2/include/FileGDBAPI.h"
#include "Marshal.h"
#include "ShapeBufferNet.h"
#include "RasterNet.h"
#include "ByteArrayNet.h"

using namespace std;
using namespace System;
using namespace Runtime::InteropServices;

namespace FileGDB_DotNet 
{
	public ref class RowNet
	{
	public:
		RowNet() : fgdbApiRow(new FileGDBAPI::Row) {};

		~RowNet() 
		{
			delete fgdbApiRow;
		}

		FileGDBAPI::Row* fgdbApiRow;

		bool IsNull(String^ field);
		void SetNull(String^ field);
		long GetOID();
		Guid^ GetGlobalID();
		FileGDB_DotNet::ShapeBufferNet^ GetGeometry();
		void SetGeometry(FileGDB_DotNet::ShapeBufferNet^ shapeBuffer);
		short GetShort(String^ field);
		void SetShort(String^ field, short value);
		long GetInteger(String^ field);
		void SetInteger(String^ field, long value);
		float GetFloat(String^ field);
		void SetFloat(String^ field, float value);
		double GetDouble(String^ field);
		void SetDouble(String^ field, double value);
		System::DateTime^ GetDate(String^ field);
		void SetDate(String^ field, System::DateTime value);
		String^ GetString(String^ field);
		void SetString(String^ field, String^ value);
		Guid^ GetGUID(String^ field);
		void SetGUID(String^ field, Guid value);
		String^ GetXML(String^ field);
		void SetXML(String^ field, String^ value);
		FileGDB_DotNet::RasterNet^ GetRaster(String^ field);
		void SetRaster(String^ field, FileGDB_DotNet::RasterNet^ value);
		FileGDB_DotNet::ByteArrayNet^ GetBinary(String^ field);
		void SetBinary(String^ field, FileGDB_DotNet::ByteArrayNet^ value);

	protected:
		!RowNet() {
			delete fgdbApiRow;
		}
	};
}