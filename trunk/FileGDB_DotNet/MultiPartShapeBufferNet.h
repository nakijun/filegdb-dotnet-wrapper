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

		EnvelopeNet^ GetExtent();
		void SetExtent(EnvelopeNet^ extent);
		int GetNumParts();
		int GetNumPoints();
		void GetParts([Out] array<int>^ %parts);
		void SetParts(array<int>^ parts);
		void GetPoints([Out] array<PointNet^>^ %points);
		void SetPoints(array<PointNet^>^ points);
		void GetZExtent([Out] array<double>^ %zExtent);
		void SetZExtent(array<double>^ zExtent);
		void GetZs([Out] array<double>^ %zArray);
		void SetZs(array<double>^ zArray);
		void GetMExtent([Out] array<double>^ %mExtent);
		void SetMExtent(array<double>^ mExtent);
		void GetMs([Out] array<double>^ %mArray);
		void SetMs(array<double>^ mArray);
		int GetNumCurves();
		//fgdbError GetCurves(byte*& %curves);
		void GetIDs([Out] array<int>^ %idArray);
		void SetIDs(array<int>^ idArray);

		void Setup(ShapeTypeNet shapeType, int numParts, int numPoints, int numCurves);

		void CalculateExtent(void);
	};
}