/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#include "stdafx.h"

#include "ShapeBufferNet.h"

namespace FileGDB_DotNet 
{
	bool ShapeBufferNet::Allocate(unsigned long length)
	{
		return fgdbApiShapeBuffer->Allocate(length);
	}
}