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
	public ref class MultiPartShapeBufferNet : ShapeBufferNet
	{
	public:
		MultiPartShapeBufferNet() : ShapeBufferNet() {};
		MultiPartShapeBufferNet(unsigned long length) : ShapeBufferNet(length) {};

		void GetExtent([Out] array<double>^ extent);
		int GetNumParts();
		int GetNumPoints();
		void GetParts([Out] array<int>^ parts);
		void GetPoints([Out] array<PointNet^>^ points);
		void GetZExtent([Out] array<double>^ zExtent);
		void GetZs([Out] array<double>^ zArray);
		void GetMExtent([Out] array<double>^ mExtent);
		void GetMs([Out] array<double>^ mArray);
		int GetNumCurves();
		//fgdbError GetCurves(byte*& curves);
		void GetIDs([Out] array<int>^ idArray);

		void Setup(int shapeType, int numParts, int numPoints, int numCurves);

		void CalculateExtent(void);
	};
}