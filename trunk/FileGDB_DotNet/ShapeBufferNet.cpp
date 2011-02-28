// This is the main DLL file.

#include "stdafx.h"

#include "ShapeBufferNet.h"

namespace FileGDB_DotNet 
{
	bool ShapeBufferNet::Allocate(unsigned long length)
	{
		return fgdbApiShapeBuffer->Allocate(length);
	}
}