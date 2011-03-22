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
	public ref class MultiPointShapeBufferNet : ShapeBufferNet
	{
	public:
		MultiPointShapeBufferNet() : ShapeBufferNet() {};
		MultiPointShapeBufferNet(unsigned long length) : ShapeBufferNet(length) {};

		void GetExtent([Out] array<double>^ extent);
		int GetNumPoints();
		void GetPoints([Out] array<PointNet^>^ points);
		void GetZExtent([Out] array<double>^ zExtent);
		void GetZs([Out] array<double>^ zArray);
		void GetMExtent([Out] array<double>^ mExtent);
		void GetMs([Out] array<double>^ mArray);
		void GetIDs([Out] array<int>^ idArray);

		void Setup(int shapeType, int numPoints);

		void CalculateExtent(void);
	};
}