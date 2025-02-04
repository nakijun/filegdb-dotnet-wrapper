/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#pragma once

#define EXT_FILEGDB_API _declspec(dllimport)
#pragma warning (disable : 4251)

#include "FileGDBAPI.h"

#include "ShapeBufferNet.h"

namespace FileGDB_DotNet 
{
	public ref class PointShapeBufferNet : ShapeBufferNet
	{
	public:
		PointShapeBufferNet() : ShapeBufferNet() {};
		PointShapeBufferNet(unsigned long length) : ShapeBufferNet(length) {};

		void GetPoints([Out] array<PointNet^>^ %points);
		void SetPoints(array<PointNet^>^ points);
		void GetZs([Out] array<double>^ %zArray);
		void SetZs(array<double>^ zArray);
		void GetMs([Out] array<double>^ %mArray);
		void SetMs(array<double>^ mArray);
		void GetIDs([Out] array<int>^ %idArray);
		void SetIDs(array<int>^ idArray);

		void Setup(ShapeTypeNet shapeType);
	};
}