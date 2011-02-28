#pragma once

#define EXT_FILEGDB_API _declspec(dllimport)
#pragma warning (disable : 4251)

#include "FileGDB_API_1_0_beta2/include/FileGDBAPI.h"

using namespace std;
using namespace System;
using namespace Runtime::InteropServices;

namespace FileGDB_DotNet 
{
	public ref class ShapeBufferNet
	{
	public:
		ShapeBufferNet(unsigned long length) : fgdbApiShapeBuffer(new FileGDBAPI::ShapeBuffer(length)) {};

		~ShapeBufferNet() 
		{
			delete fgdbApiShapeBuffer;
		}

		FileGDBAPI::ShapeBuffer* fgdbApiShapeBuffer;

		bool Allocate(unsigned long length);

		property unsigned long allocatedLength
		{
			unsigned long get() { return fgdbApiShapeBuffer->allocatedLength; }
			void set(unsigned long value) { fgdbApiShapeBuffer->allocatedLength = value; }
		}

		property unsigned long inUseLength
		{
			unsigned long get() { return fgdbApiShapeBuffer->inUseLength; }
			void set(unsigned long value) { fgdbApiShapeBuffer->inUseLength = value; }
		}

	protected:
		!ShapeBufferNet() {
			delete fgdbApiShapeBuffer;
		}
	};
}