/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#include "stdafx.h"

#include "FGDBException.h"
#include "ShapeBufferNet.h"

namespace FileGDB_DotNet 
{
	bool ShapeBufferNet::Allocate(unsigned long length)
	{
		return this->fgdbApiShapeBuffer->Allocate(length);
	}

	ShapeTypeNet ShapeBufferNet::GetShapeType() 
	{
		FileGDBAPI::ShapeType shapeType;
		fgdbError hr;
		if ((hr = this->fgdbApiShapeBuffer->GetShapeType(shapeType)) != S_OK) {
			throw gcnew FGDBException("Error getting shape type.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
		return (ShapeTypeNet)shapeType;
	}

#pragma region "Static Methods"

	bool ShapeBufferNet::HasZs(FileGDBAPI::ShapeType shapeType)
	{
		return FileGDBAPI::ShapeBuffer::HasZs(shapeType);
	}

	bool ShapeBufferNet::HasMs(FileGDBAPI::ShapeType shapeType)
	{
		return FileGDBAPI::ShapeBuffer::HasMs(shapeType);
	}

	bool ShapeBufferNet::HasIDs(FileGDBAPI::ShapeType shapeType)
	{
		return FileGDBAPI::ShapeBuffer::HasIDs(shapeType);
	}

	bool ShapeBufferNet::HasCurves(FileGDBAPI::ShapeType shapeType)
	{
		return FileGDBAPI::ShapeBuffer::HasCurves(shapeType);
	}

	bool ShapeBufferNet::HasNormals(FileGDBAPI::ShapeType shapeType)
	{
		return FileGDBAPI::ShapeBuffer::HasNormals(shapeType);
	}

	bool ShapeBufferNet::HasTextures(FileGDBAPI::ShapeType shapeType)
	{
		return FileGDBAPI::ShapeBuffer::HasTextures(shapeType);
	}

	bool ShapeBufferNet::HasMaterials(FileGDBAPI::ShapeType shapeType)
	{
		return FileGDBAPI::ShapeBuffer::HasMaterials(shapeType);
	}

	int ShapeBufferNet::GeometryType(FileGDBAPI::ShapeType shapeType)
	{
		return FileGDBAPI::ShapeBuffer::GetGeometryType(shapeType);
	}

#pragma endregion
}