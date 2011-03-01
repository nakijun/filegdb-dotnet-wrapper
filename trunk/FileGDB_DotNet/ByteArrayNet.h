/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#pragma once

#define EXT_FILEGDB_API _declspec(dllimport)
#pragma warning (disable : 4251)

#include "FileGDB_API_1_0_beta2/include/FileGDBAPI.h"

using namespace std;
using namespace System;
using namespace Runtime::InteropServices;

namespace FileGDB_DotNet 
{
	public ref class ByteArrayNet
	{
	public:
		ByteArrayNet(unsigned long length) : fgdbApiByteArray(new FileGDBAPI::ByteArray(length)) {};

		~ByteArrayNet() 
		{
			delete fgdbApiByteArray;
		}

		FileGDBAPI::ByteArray* fgdbApiByteArray;

		

		bool Allocate(unsigned long length);

		property unsigned long allocatedLength
		{
			unsigned long get() { return fgdbApiByteArray->allocatedLength; }
			void set(unsigned long value) { fgdbApiByteArray->allocatedLength = value; }
		}

		property unsigned long inUseLength
		{
			unsigned long get() { return fgdbApiByteArray->inUseLength; }
			void set(unsigned long value) { fgdbApiByteArray->inUseLength = value; }
		}

	protected:
		!ByteArrayNet() {
			delete fgdbApiByteArray;
		}
	};
}