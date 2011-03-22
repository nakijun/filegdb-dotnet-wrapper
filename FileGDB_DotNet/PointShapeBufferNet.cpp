/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#include "stdafx.h"

#include "FGDBException.h"
#include "PointShapeBufferNet.h"

namespace FileGDB_DotNet 
{
	void PointShapeBufferNet::GetPoints([Out] array<PointNet^>^ points)
	{
		fgdbError hr;
		FileGDBAPI::Point* inPoints;
		FileGDBAPI::PointShapeBuffer* psb = (FileGDBAPI::PointShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = psb->GetPoints(inPoints)) != S_OK) {
			throw gcnew FGDBException("Error getting XY values.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		points = gcnew array<PointNet^>(1);
		points[0] = gcnew PointNet(inPoints[0].x, inPoints[0].y);
	}

	void PointShapeBufferNet::GetZs([Out] array<double>^ zArray)
	{
		fgdbError hr;
		double* inZArray;
		FileGDBAPI::PointShapeBuffer* psb = (FileGDBAPI::PointShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = psb->GetZs(inZArray)) != S_OK) {
			throw gcnew FGDBException("Error getting Z values.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		zArray = gcnew array<double>(1);
		zArray[0] = inZArray[0];
	}

	void PointShapeBufferNet::GetMs([Out] array<double>^ mArray)
	{
		fgdbError hr;
		double* inMArray;
		FileGDBAPI::PointShapeBuffer* psb = (FileGDBAPI::PointShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = psb->GetMs(inMArray)) != S_OK) {
			throw gcnew FGDBException("Error getting M values.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		mArray = gcnew array<double>(1);
		mArray[0] = inMArray[0];
	}

	void PointShapeBufferNet::GetIDs([Out] array<int>^ idArray)
	{
		fgdbError hr;
		int* inIdArray;
		FileGDBAPI::PointShapeBuffer* psb = (FileGDBAPI::PointShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = psb->GetIDs(inIdArray)) != S_OK) {
			throw gcnew FGDBException("Error getting IDs.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		idArray = gcnew array<int>(1);
		idArray[0] = inIdArray[0];
	}

	void PointShapeBufferNet::Setup(int shapeType)
	{
		fgdbError hr;
		FileGDBAPI::PointShapeBuffer* psb = (FileGDBAPI::PointShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = psb->Setup(shapeType)) != S_OK) {
			throw gcnew FGDBException("Error setting up.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}
}