/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#include "stdafx.h"

#include "FGDBException.h"
#include "MultiPartShapeBufferNet.h"

namespace FileGDB_DotNet 
{
	EnvelopeNet^ MultiPartShapeBufferNet::GetExtent()
	{
		fgdbError hr;
		double* inExtent;
		FileGDBAPI::MultiPartShapeBuffer* mpsb = (FileGDBAPI::MultiPartShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->GetExtent(inExtent)) != S_OK) {
			throw gcnew FGDBException("Error getting extent.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return gcnew EnvelopeNet(inExtent[0], inExtent[2],inExtent[1], inExtent[3]);
	}

	void MultiPartShapeBufferNet::SetExtent(EnvelopeNet^ extent)
	{
		fgdbError hr;
		double* inExtent;
		FileGDBAPI::MultiPartShapeBuffer* mpsb = (FileGDBAPI::MultiPartShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->GetExtent(inExtent)) != S_OK) {
			throw gcnew FGDBException("Error getting extent.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		inExtent[0] = extent->XMin;
		inExtent[1] = extent->YMin;
		inExtent[2] = extent->XMax;
		inExtent[3] = extent->YMax;
	}

	int MultiPartShapeBufferNet::GetNumParts()
	{
		fgdbError hr;
		int numParts;
		FileGDBAPI::MultiPartShapeBuffer* mpsb = (FileGDBAPI::MultiPartShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->GetNumParts(numParts)) != S_OK) {
			throw gcnew FGDBException("Error getting number of parts.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return numParts;
	}
	
	int MultiPartShapeBufferNet::GetNumPoints()
	{
		fgdbError hr;
		int numPoints;
		FileGDBAPI::MultiPartShapeBuffer* mpsb = (FileGDBAPI::MultiPartShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->GetNumPoints(numPoints)) != S_OK) {
			throw gcnew FGDBException("Error getting number of points.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return numPoints;
	}

	void MultiPartShapeBufferNet::GetParts([Out] array<int>^ %parts)
	{
		fgdbError hr;
		int* inParts;
		FileGDBAPI::MultiPartShapeBuffer* mpsb = (FileGDBAPI::MultiPartShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->GetParts(inParts)) != S_OK) {
			throw gcnew FGDBException("Error getting parts.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		int numParts = this->GetNumParts();
		parts = gcnew array<int>(numParts);
		for (int i=0; i<numParts; i++)
			parts[i] = inParts[i];
	}

	void MultiPartShapeBufferNet::SetParts(array<int>^ parts)
	{
		int numParts = this->GetNumParts();

		if (parts == nullptr || parts->Length != numParts)
			throw gcnew Exception("Error setting parts.  You must supply an array of exactly " + numParts + " values.");

		fgdbError hr;
		int* inParts;
		FileGDBAPI::MultiPartShapeBuffer* mpsb = (FileGDBAPI::MultiPartShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->GetParts(inParts)) != S_OK) {
			throw gcnew FGDBException("Error getting parts.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		for (int i=0; i<numParts; i++)
			inParts[i] = parts[i];
	}
	
	void MultiPartShapeBufferNet::GetPoints([Out] array<PointNet^>^ %points)
	{
		fgdbError hr;
		FileGDBAPI::Point* inPoints;
		FileGDBAPI::MultiPartShapeBuffer* mpsb = (FileGDBAPI::MultiPartShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->GetPoints(inPoints)) != S_OK) {
			throw gcnew FGDBException("Error getting XY values.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		int numPoints = this->GetNumPoints();
		points = gcnew array<PointNet^>(numPoints);
		for (int i=0; i<numPoints; i++)
			points[i] = gcnew PointNet(inPoints[i].x, inPoints[i].y);
	}

	void MultiPartShapeBufferNet::SetPoints(array<PointNet^>^ points)
	{
		int numPoints = this->GetNumPoints();

		if (points == nullptr || points->Length != numPoints)
			throw gcnew Exception("Error setting points.  You must supply an array of exactly " + numPoints + " points.");

		fgdbError hr;
		FileGDBAPI::Point* inPoints;
		FileGDBAPI::MultiPartShapeBuffer* mpsb = (FileGDBAPI::MultiPartShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->GetPoints(inPoints)) != S_OK) {
			throw gcnew FGDBException("Error getting XY values.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
		
		for (int i=0; i<numPoints; i++) {
			inPoints[i].x = points[i]->x;
			inPoints[i].y = points[i]->y;
		}
	}

	void MultiPartShapeBufferNet::GetZExtent([Out] array<double>^ %zExtent)
	{
		fgdbError hr;
		double* inZExtent;
		FileGDBAPI::MultiPartShapeBuffer* mpsb = (FileGDBAPI::MultiPartShapeBuffer*)this->fgdbApiShapeBuffer;
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

	void MultiPartShapeBufferNet::SetZExtent(array<double>^ zExtent)
	{
		if (zExtent == nullptr || zExtent->Length != 4)
			throw gcnew Exception("Error setting extent.  You must supply an array of exactly 4 values.");

		fgdbError hr;
		double* inZExtent;
		FileGDBAPI::MultiPartShapeBuffer* mpsb = (FileGDBAPI::MultiPartShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->GetZExtent(inZExtent)) != S_OK) {
			throw gcnew FGDBException("Error getting Z extent.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		// TODO: Verify to make sure extent is in fact returned as 4 doubles
		// TODO: Return an Envelope instead of a double array?
		inZExtent[0] = zExtent[0];
		inZExtent[1] = zExtent[1];
		inZExtent[2] = zExtent[2];
		inZExtent[3] = zExtent[3];
	}

	void MultiPartShapeBufferNet::GetZs([Out] array<double>^ %zArray)
	{
		fgdbError hr;
		double* inZArray;
		FileGDBAPI::MultiPartShapeBuffer* mpsb = (FileGDBAPI::MultiPartShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->GetZs(inZArray)) != S_OK) {
			throw gcnew FGDBException("Error getting Z values.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		int numPoints = this->GetNumPoints();
		zArray = gcnew array<double>(numPoints);
		for (int i=0; i<numPoints; i++)
			zArray[i] = inZArray[i];
	}

	void MultiPartShapeBufferNet::SetZs(array<double>^ zArray)
	{
		int numPoints = this->GetNumPoints();

		if (zArray == nullptr || zArray->Length != numPoints)
			throw gcnew Exception("Error setting Z values.  You must supply an array of exactly " + numPoints + " points.");

		fgdbError hr;
		double* inZArray;
		FileGDBAPI::MultiPartShapeBuffer* mpsb = (FileGDBAPI::MultiPartShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->GetZs(inZArray)) != S_OK) {
			throw gcnew FGDBException("Error getting Z values.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		for (int i=0; i<numPoints; i++)
			inZArray[i] = zArray[i];
	}

	void MultiPartShapeBufferNet::GetMExtent([Out] array<double>^ %mExtent)
	{
		fgdbError hr;
		double* inMExtent;
		FileGDBAPI::MultiPartShapeBuffer* mpsb = (FileGDBAPI::MultiPartShapeBuffer*)this->fgdbApiShapeBuffer;
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

	void MultiPartShapeBufferNet::SetMExtent(array<double>^ mExtent)
	{
		if (mExtent == nullptr || mExtent->Length != 4)
			throw gcnew Exception("Error setting extent.  You must supply an array of exactly 4 values.");

		fgdbError hr;
		double* inMExtent;
		FileGDBAPI::MultiPartShapeBuffer* mpsb = (FileGDBAPI::MultiPartShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->GetMExtent(inMExtent)) != S_OK) {
			throw gcnew FGDBException("Error getting M extent.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		// TODO: Verify to make sure extent is in fact returned as 4 doubles
		// TODO: Return an Envelope instead of a double array?
		inMExtent[0] = mExtent[0];
		inMExtent[1] = mExtent[1];
		inMExtent[2] = mExtent[2];
		inMExtent[3] = mExtent[3];
	}

	void MultiPartShapeBufferNet::GetMs([Out] array<double>^ %mArray)
	{
		fgdbError hr;
		double* inMArray;
		FileGDBAPI::MultiPartShapeBuffer* mpsb = (FileGDBAPI::MultiPartShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->GetMs(inMArray)) != S_OK) {
			throw gcnew FGDBException("Error getting M values.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		int numPoints = this->GetNumPoints();
		mArray = gcnew array<double>(numPoints);
		for (int i=0; i<numPoints; i++)
			mArray[i] = inMArray[i];
	}

	void MultiPartShapeBufferNet::SetMs(array<double>^ mArray)
	{
		int numPoints = this->GetNumPoints();

		if (mArray == nullptr || mArray->Length != numPoints)
			throw gcnew Exception("Error setting M values.  You must supply an array of exactly " + numPoints + " points.");

		fgdbError hr;
		double* inMArray;
		FileGDBAPI::MultiPartShapeBuffer* mpsb = (FileGDBAPI::MultiPartShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->GetMs(inMArray)) != S_OK) {
			throw gcnew FGDBException("Error getting M values.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		for (int i=0; i<numPoints; i++)
			inMArray[i] = mArray[i];
	}

	int MultiPartShapeBufferNet::GetNumCurves()
	{
		fgdbError hr;
		int numCurves;
		FileGDBAPI::MultiPartShapeBuffer* mpsb = (FileGDBAPI::MultiPartShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->GetNumCurves(numCurves)) != S_OK) {
			throw gcnew FGDBException("Error getting number of curves.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return numCurves;
	}

	void MultiPartShapeBufferNet::GetIDs([Out] array<int>^ %idArray)
	{
		fgdbError hr;
		int* inIdArray;
		FileGDBAPI::MultiPartShapeBuffer* mpsb = (FileGDBAPI::MultiPartShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->GetIDs(inIdArray)) != S_OK) {
			throw gcnew FGDBException("Error getting IDs.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		int numPoints = this->GetNumPoints();
		idArray = gcnew array<int>(numPoints);
		for (int i=0; i<numPoints; i++)
			idArray[i] = inIdArray[i];
	}

	void MultiPartShapeBufferNet::SetIDs(array<int>^ idArray)
	{
		int numPoints = this->GetNumPoints();

		if (idArray == nullptr || idArray->Length != numPoints)
			throw gcnew Exception("Error setting ID values.  You must supply an array of exactly " + numPoints + " points.");

		fgdbError hr;
		int* inIdArray;
		FileGDBAPI::MultiPartShapeBuffer* mpsb = (FileGDBAPI::MultiPartShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->GetIDs(inIdArray)) != S_OK) {
			throw gcnew FGDBException("Error getting M values.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		for (int i=0; i<numPoints; i++)
			inIdArray[i] = idArray[i];
	}
	
	void MultiPartShapeBufferNet::Setup(ShapeTypeNet shapeType, int numParts, int numPoints, int numCurves)
	{
		fgdbError hr;
		FileGDBAPI::MultiPartShapeBuffer* mpsb = (FileGDBAPI::MultiPartShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->Setup((FileGDBAPI::ShapeType)shapeType, numParts, numPoints, numCurves)) != S_OK) {
			throw gcnew FGDBException("Error setting up.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}
	
	void MultiPartShapeBufferNet::CalculateExtent(void)
	{
		fgdbError hr;
		FileGDBAPI::MultiPartShapeBuffer* mpsb = (FileGDBAPI::MultiPartShapeBuffer*)this->fgdbApiShapeBuffer;
		if ((hr = mpsb->CalculateExtent()) != S_OK) {
			throw gcnew FGDBException("Error calculating extent.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}
}