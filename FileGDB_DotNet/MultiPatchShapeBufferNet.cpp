/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#include "stdafx.h"

#include "FGDBException.h"
#include "MultiPatchShapeBufferNet.h"

namespace FileGDB_DotNet 
{
	void MultiPatchShapeBufferNet::GetExtent([Out] array<double>^ extent)
	{
		fgdbError hr;
		double* inExtent;
		FileGDBAPI::MultiPatchShapeBuffer* mpsb = (FileGDBAPI::MultiPatchShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->GetExtent(inExtent)) != S_OK) {
			throw gcnew FGDBException("Error getting extent.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		// TODO: Verify to make sure extent is in fact returned as 4 doubles
		// TODO: Return an Envelope instead of a double array?
		extent = gcnew array<double>(4);
		extent[0] = inExtent[0];
		extent[1] = inExtent[1];
		extent[2] = inExtent[2];
		extent[3] = inExtent[3];
	}

	int MultiPatchShapeBufferNet::GetNumParts()
	{
		fgdbError hr;
		int numParts;
		FileGDBAPI::MultiPatchShapeBuffer* mpsb = (FileGDBAPI::MultiPatchShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->GetNumParts(numParts)) != S_OK) {
			throw gcnew FGDBException("Error getting number of parts.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return numParts;
	}
	
	int MultiPatchShapeBufferNet::GetNumPoints()
	{
		fgdbError hr;
		int numPoints;
		FileGDBAPI::MultiPatchShapeBuffer* mpsb = (FileGDBAPI::MultiPatchShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->GetNumPoints(numPoints)) != S_OK) {
			throw gcnew FGDBException("Error getting number of points.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return numPoints;
	}

	void MultiPatchShapeBufferNet::GetParts([Out] array<int>^ parts)
	{
		fgdbError hr;
		int* inParts;
		FileGDBAPI::MultiPatchShapeBuffer* mpsb = (FileGDBAPI::MultiPatchShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->GetParts(inParts)) != S_OK) {
			throw gcnew FGDBException("Error getting parts.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		int numPoints = this->GetNumPoints();
		parts = gcnew array<int>(numPoints);
		for (int i=0; i<numPoints; i++)
			parts[i] = inParts[i];
	}

	void MultiPatchShapeBufferNet::GetPartDescriptors([Out] array<int>^ parts)
	{
		fgdbError hr;
		int* inParts;
		FileGDBAPI::MultiPatchShapeBuffer* mpsb = (FileGDBAPI::MultiPatchShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->GetPartDescriptors(inParts)) != S_OK) {
			throw gcnew FGDBException("Error getting part descriptors.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		int numPoints = this->GetNumPoints();
		parts = gcnew array<int>(numPoints);
		for (int i=0; i<numPoints; i++)
			parts[i] = inParts[i];
	}
	
	void MultiPatchShapeBufferNet::GetPoints([Out] array<PointNet^>^ points)
	{
		fgdbError hr;
		FileGDBAPI::Point* inPoints;
		FileGDBAPI::MultiPatchShapeBuffer* mpsb = (FileGDBAPI::MultiPatchShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->GetPoints(inPoints)) != S_OK) {
			throw gcnew FGDBException("Error getting XY values.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		int numPoints = this->GetNumPoints();
		points = gcnew array<PointNet^>(numPoints);
		for (int i=0; i<numPoints; i++)
			points[i] = gcnew PointNet(inPoints[i].x, inPoints[i].y);
	}

	void MultiPatchShapeBufferNet::GetZExtent([Out] array<double>^ zExtent)
	{
		fgdbError hr;
		double* inZExtent;
		FileGDBAPI::MultiPatchShapeBuffer* mpsb = (FileGDBAPI::MultiPatchShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->GetZExtent(inZExtent)) != S_OK) {
			throw gcnew FGDBException("Error getting Z extent.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		// TODO: Verify to make sure extent is in fact returned as 4 doubles
		// TODO: Return an Envelope instead of a double array?
		zExtent = gcnew array<double>(4);
		zExtent[0] = inZExtent[0];
		zExtent[1] = inZExtent[1];
		zExtent[2] = inZExtent[2];
		zExtent[3] = inZExtent[3];
	}

	void MultiPatchShapeBufferNet::GetZs([Out] array<double>^ zArray)
	{
		fgdbError hr;
		double* inZArray;
		FileGDBAPI::MultiPatchShapeBuffer* mpsb = (FileGDBAPI::MultiPatchShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->GetZs(inZArray)) != S_OK) {
			throw gcnew FGDBException("Error getting Z values.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		int numPoints = this->GetNumPoints();
		zArray = gcnew array<double>(numPoints);
		for (int i=0; i<numPoints; i++)
			zArray[i] = inZArray[i];
	}

	void MultiPatchShapeBufferNet::GetMExtent([Out] array<double>^ mExtent)
	{
		fgdbError hr;
		double* inMExtent;
		FileGDBAPI::MultiPatchShapeBuffer* mpsb = (FileGDBAPI::MultiPatchShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->GetMExtent(inMExtent)) != S_OK) {
			throw gcnew FGDBException("Error getting M extent.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		// TODO: Verify to make sure extent is in fact returned as 4 doubles
		// TODO: Return an Envelope instead of a double array?
		mExtent = gcnew array<double>(4);
		mExtent[0] = inMExtent[0];
		mExtent[1] = inMExtent[1];
		mExtent[2] = inMExtent[2];
		mExtent[3] = inMExtent[3];
	}

	void MultiPatchShapeBufferNet::GetMs([Out] array<double>^ mArray)
	{
		fgdbError hr;
		double* inMArray;
		FileGDBAPI::MultiPatchShapeBuffer* mpsb = (FileGDBAPI::MultiPatchShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->GetMs(inMArray)) != S_OK) {
			throw gcnew FGDBException("Error getting M values.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		int numPoints = this->GetNumPoints();
		mArray = gcnew array<double>(numPoints);
		for (int i=0; i<numPoints; i++)
			mArray[i] = inMArray[i];
	}

	void MultiPatchShapeBufferNet::GetIDs([Out] array<int>^ idArray)
	{
		fgdbError hr;
		int* inIdArray;
		FileGDBAPI::MultiPatchShapeBuffer* mpsb = (FileGDBAPI::MultiPatchShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->GetIDs(inIdArray)) != S_OK) {
			throw gcnew FGDBException("Error getting IDs.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		int numPoints = this->GetNumPoints();
		idArray = gcnew array<int>(numPoints);
		for (int i=0; i<numPoints; i++)
			idArray[i] = inIdArray[i];
	}
	
	void MultiPatchShapeBufferNet::Setup(int shapeType, int numParts, int numPoints, int numCurves)
	{
		fgdbError hr;
		FileGDBAPI::MultiPatchShapeBuffer* mpsb = (FileGDBAPI::MultiPatchShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->Setup(shapeType, numParts, numPoints, numCurves)) != S_OK) {
			throw gcnew FGDBException("Error setting up.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}
	
	void MultiPatchShapeBufferNet::CalculateExtent(void)
	{
		fgdbError hr;
		FileGDBAPI::MultiPatchShapeBuffer* mpsb = (FileGDBAPI::MultiPatchShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->CalculateExtent()) != S_OK) {
			throw gcnew FGDBException("Error calculating extent.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}
}