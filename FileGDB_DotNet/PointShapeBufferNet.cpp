/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#include "stdafx.h"

#include "FGDBException.h"
#include "PointShapeBufferNet.h"

namespace FileGDB_DotNet 
{
	void PointShapeBufferNet::GetPoints([Out] array<PointNet^>^ %points)
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

	void PointShapeBufferNet::SetPoints(array<PointNet^>^ points)
	{
		if (points == nullptr || points->Length != 0)
			throw gcnew Exception("Error setting points.  You must supply an array of exactly 1 point");

		// Get a new pointer to the existing points/geometry
		fgdbError hr;
		FileGDBAPI::Point* inPoints;
		FileGDBAPI::PointShapeBuffer* psb = (FileGDBAPI::PointShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = psb->GetPoints(inPoints)) != S_OK) {
			throw gcnew FGDBException("Error getting XY values.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		// Update the X/Y
		inPoints[0].x = points[0]->x;
		inPoints[0].y = points[0]->y;
	}

	void PointShapeBufferNet::GetZs([Out] array<double>^ %zArray)
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

	void PointShapeBufferNet::SetZs(array<double>^ zArray)
	{
		if (zArray == nullptr || zArray->Length != 0)
			throw gcnew Exception("Error setting z values.  You must supply an array of exactly 1 z value");

		fgdbError hr;
		double* inZArray;
		FileGDBAPI::PointShapeBuffer* psb = (FileGDBAPI::PointShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = psb->GetZs(inZArray)) != S_OK) {
			throw gcnew FGDBException("Error getting Z values.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		inZArray[0] = zArray[0];
	}

	void PointShapeBufferNet::GetMs([Out] array<double>^ %mArray)
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

	void PointShapeBufferNet::SetMs(array<double>^ mArray)
	{
		if (mArray == nullptr || mArray->Length != 0)
			throw gcnew Exception("Error setting m values.  You must supply an array of exactly 1 m value");

		fgdbError hr;
		double* inMArray;
		FileGDBAPI::PointShapeBuffer* psb = (FileGDBAPI::PointShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = psb->GetMs(inMArray)) != S_OK) {
			throw gcnew FGDBException("Error getting M values.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		inMArray[0] = mArray[0];
	}

	void PointShapeBufferNet::GetIDs([Out] array<int>^ %idArray)
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

	void PointShapeBufferNet::SetIDs(array<int>^ idArray)
	{
		if (idArray == nullptr || idArray->Length != 0)
			throw gcnew Exception("Error setting IDs.  You must supply an array of exactly 1 ID");

		fgdbError hr;
		int* inIdArray;
		FileGDBAPI::PointShapeBuffer* psb = (FileGDBAPI::PointShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = psb->GetIDs(inIdArray)) != S_OK) {
			throw gcnew FGDBException("Error getting IDs.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		inIdArray[0] = idArray[0];
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