/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#pragma once

namespace FileGDB_DotNet 
{
	public ref class GeometryNet
	{
	public:
		GeometryNet(long shapeType)
		{
			this->ShapeType = shapeType;
		}

		long ShapeType;
	};
}