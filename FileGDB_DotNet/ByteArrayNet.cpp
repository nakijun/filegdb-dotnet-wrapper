/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */

#include "stdafx.h"

#include "ByteArrayNet.h"

namespace FileGDB_DotNet 
{
	bool ByteArrayNet::Allocate(unsigned long length)
	{
		return fgdbApiByteArray->Allocate(length);
	}
}