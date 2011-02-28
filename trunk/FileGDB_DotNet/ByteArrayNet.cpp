// This is the main DLL file.

#include "stdafx.h"

#include "ByteArrayNet.h"

namespace FileGDB_DotNet 
{
	bool ByteArrayNet::Allocate(unsigned long length)
	{
		return fgdbApiByteArray->Allocate(length);
	}
}