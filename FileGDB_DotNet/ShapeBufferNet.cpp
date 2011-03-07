/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#include "stdafx.h"

#include "ShapeBufferNet.h"

namespace FileGDB_DotNet 
{
#pragma pack(push)
#pragma pack(8)
	struct WKPoint {
		double x;
		double y;
	};
#pragma pack(pop)

#pragma pack(push)
#pragma pack(8)
	struct WKEnvelope {
		double xmin;
		double ymin;
		double xmax;
		double ymax;
	};
#pragma pack(pop)

#pragma pack(push)
#pragma pack(4)
	struct WKPolylineHeader {
		WKEnvelope extent;
		long numParts;
		long numPoints;
	};
#pragma pack(pop)

#pragma pack(push)
#pragma pack(4)
	struct WKPolygonHeader {
		WKEnvelope extent;
		long numPaths;
		long numPoints;
	};
#pragma pack(pop)

#pragma pack(push)
#pragma pack(4)
	struct WKMultiPointHeader {
		WKEnvelope extent;
		long numPoints;
	};
#pragma pack(pop)

	bool ShapeBufferNet::Allocate(unsigned long length)
	{
		return this->fgdbApiShapeBuffer->Allocate(length);
	}

	long ShapeBufferNet::GetShapeType() 
	{
		return *((long*)this->fgdbApiShapeBuffer->shapeBuffer);
	}

	/// <summary>
	/// Returns the .NET representation of the geometry found
	/// in the ShapeBuffer.
	/// </summary>
	GeometryNet^ ShapeBufferNet::GetGeometry() 
	{
		long shpType = this->GetShapeType();

		if (shpType == 1) {
			return this->GetPoint();
		} else if (shpType == 3) {
			return this->GetPolyline();
		} else if (shpType == 5) {
			return this->GetPolygon();
		} else if (shpType == 8) {
			return this->GetMultipoint();
		} else {
			// Unsupported shape type
			return nullptr;
		}
		
	}

	PointNet^ ShapeBufferNet::GetPoint()
	{
		long shpType = this->GetShapeType();
		WKPoint* pt = (WKPoint*)(this->fgdbApiShapeBuffer->shapeBuffer+sizeof(shpType));
		return gcnew PointNet((*pt).x, (*pt).y);
	}

	PolylineNet^ ShapeBufferNet::GetPolyline()
	{
		PolylineNet^ pl = gcnew PolylineNet();
		
		long offset = sizeof(long);
		WKPolylineHeader* header = (WKPolylineHeader*)(this->fgdbApiShapeBuffer->shapeBuffer+offset);
		pl->Extent->XMin = (*header).extent.xmin;
		pl->Extent->YMin = (*header).extent.ymin;
		pl->Extent->XMax = (*header).extent.xmax;
		pl->Extent->YMax = (*header).extent.ymax;

		offset += sizeof(WKPolylineHeader);
		long numParts = (*header).numParts;
		long numPoints = (*header).numPoints;
		
		long* parts = (long*)(this->fgdbApiShapeBuffer->shapeBuffer+offset);
		offset += numParts*sizeof(long);
		WKPoint* points = (WKPoint*)(this->fgdbApiShapeBuffer->shapeBuffer+offset);

		pl->Parts = gcnew array<array<PointNet^>^>(numParts);
		long totPoints = 0;
		for (long i=0; i<numParts; i++) {
			if (i < numParts-1) {
				// Total points is the next part index minus current part index
				totPoints = *(parts+i+1) - *(parts+i);
			} else {
				// No next part index, use total # of points in the array minus current part idx
				totPoints = numPoints - *(parts+i);
			}

			pl->Parts[i] = gcnew array<PointNet^>(totPoints);
			for (long j=0; j<totPoints; j++) {
				pl->Parts[i][j] = gcnew PointNet((*points).x, (*points).y);
				points++;
			}
		}

		return pl;
	}

	PolygonNet^ ShapeBufferNet::GetPolygon()
	{
		PolygonNet^ pg = gcnew PolygonNet();
		
		long offset = sizeof(long);

		WKPolygonHeader* header = (WKPolygonHeader*)(this->fgdbApiShapeBuffer->shapeBuffer+offset);
		pg->Extent->XMin = (*header).extent.xmin;
		pg->Extent->YMin = (*header).extent.ymin;
		pg->Extent->XMax = (*header).extent.xmax;
		pg->Extent->YMax = (*header).extent.ymax;
		long numPaths = (*header).numPaths;
		long numPoints = (*header).numPoints;

		offset += sizeof(WKPolygonHeader);

		long* paths = (long*)(this->fgdbApiShapeBuffer->shapeBuffer+offset);
		offset += numPaths*sizeof(long);
		WKPoint* points = (WKPoint*)(this->fgdbApiShapeBuffer->shapeBuffer+offset);

		pg->Paths = gcnew array<array<PointNet^>^>(numPaths);
		long totPoints = 0;
		for (long i=0; i<numPaths; i++) {
			if (i < numPaths-1) {
				// Total points is the next path index minus current path index
				totPoints = *(paths+i+1) - *(paths+i);
			} else {
				// No next path index, use total # of points in the array minus current path idx
				totPoints = numPoints - *(paths+i);
			}

			pg->Paths[i] = gcnew array<PointNet^>(totPoints);
			for (long j=0; j<totPoints; j++) {
				pg->Paths[i][j] = gcnew PointNet((*points).x, (*points).y);
				points++;
			}
		}

		return pg;
	}

	MultiPointNet^ ShapeBufferNet::GetMultipoint()
	{
		MultiPointNet^ mp = gcnew MultiPointNet();
		
		long offset = sizeof(long);
		WKMultiPointHeader* header = (WKMultiPointHeader*)(this->fgdbApiShapeBuffer->shapeBuffer+offset);
		mp->Extent->XMin = (*header).extent.xmin;
		mp->Extent->YMin = (*header).extent.ymin;
		mp->Extent->XMax = (*header).extent.xmax;
		mp->Extent->YMax = (*header).extent.ymax;
		long numPoints = (*header).numPoints;
		offset += sizeof(WKMultiPointHeader);
		
		WKPoint* points = (WKPoint*)(this->fgdbApiShapeBuffer->shapeBuffer+offset);

		mp->Points = gcnew array<PointNet^>(numPoints);
		long totPoints = 0;
		for (long i=0; i<numPoints; i++) {
			mp->Points[i] = gcnew PointNet((*points).x, (*points).y);
			points++;
		}

		return mp;
	}

	void ShapeBufferNet::SetGeometry(GeometryNet^ geometry) 
	{
		if (geometry->ShapeType == 1) {
			SetPoint((PointNet^)geometry);
		} else if (geometry->ShapeType == 3) {
			SetPolyline((PolylineNet^)geometry);
		} else if (geometry->ShapeType == 5) {
			SetPolygon((PolygonNet^)geometry);
		} else if (geometry->ShapeType == 8) {
			SetMultiPoint((MultiPointNet^)geometry);
		} else {
			throw gcnew Exception("Unsupported geometry type");
		}
	}

	void ShapeBufferNet::SetPoint(PointNet^ point) {
		// Allocate 20 bytes if necessary.  Re-allocation shouldn't be required
		// as we are overwriting all existing contents
		if (this->fgdbApiShapeBuffer->allocatedLength != 20)
			this->fgdbApiShapeBuffer->Allocate(20);

		long shapeType = point->ShapeType;
		WKPoint pt = {
			point->X,
			point->Y
		};
		memcpy(this->fgdbApiShapeBuffer->shapeBuffer, &shapeType, sizeof(shapeType));
		memcpy(this->fgdbApiShapeBuffer->shapeBuffer+sizeof(shapeType), &pt, sizeof(WKPoint));
		this->fgdbApiShapeBuffer->inUseLength = 20;
	}

	void ShapeBufferNet::SetPolyline(PolylineNet^ pline) 
	{
		// Header bytes (44 bytes) + number of parts * 4 (4 bytes for ints) + 
		// number of points * 16 (each point is 2 doubles)
		long numParts = pline->NumParts;
		long numPoints = pline->NumPoints;
		long totBytes = sizeof(long) + sizeof(WKPolylineHeader) + numParts*sizeof(long) + numPoints*sizeof(double)*2;
		// Allocate memory as necessary
		if (this->fgdbApiShapeBuffer->allocatedLength != totBytes)
			this->fgdbApiShapeBuffer->Allocate(totBytes);

		// Copy the shape type
		long shapeType = pline->ShapeType;
		memcpy(this->fgdbApiShapeBuffer->shapeBuffer, &shapeType, sizeof(shapeType));
		long offset = sizeof(long);

		// Copy the Extent
		WKPolylineHeader header = {
			pline->Extent->XMin,
			pline->Extent->YMin,
			pline->Extent->XMax,
			pline->Extent->YMax,
			numParts,
			numPoints
		};

		memcpy(this->fgdbApiShapeBuffer->shapeBuffer+offset, &header, sizeof(WKPolylineHeader));
		offset += sizeof(WKPolylineHeader);
		
		long partIdx = 0;
		long pointIdx = 0;
		double x,y;
		for (long i=0; i<numParts; i++) {
			// Copy the part index
			memcpy(this->fgdbApiShapeBuffer->shapeBuffer+offset+i*4, &partIdx, sizeof(partIdx));

			// Copy the points for this part
			for (long j=0; j<pline->Parts[i]->Length; j++) {
				x = pline->Parts[i][j]->X;
				y = pline->Parts[i][j]->Y;

				memcpy(this->fgdbApiShapeBuffer->shapeBuffer+offset+numParts*4+pointIdx, &x, sizeof(x));
				pointIdx += 8;
				memcpy(this->fgdbApiShapeBuffer->shapeBuffer+offset+numParts*4+pointIdx, &y, sizeof(y));
				pointIdx += 8;
			}

			partIdx += pline->Parts[i]->Length;
		}

		this->fgdbApiShapeBuffer->inUseLength = totBytes;
	}

	void ShapeBufferNet::SetPolygon(PolygonNet^ pgon) 
	{
		// Header bytes (44 bytes) + number of parts * 4 (4 bytes for ints) + 
		// number of points * 16 (each point is 2 doubles)
		long numPaths = pgon->NumPaths;
		long numPoints = pgon->NumPoints;
		long totBytes = sizeof(long) + sizeof(WKPolygonHeader) + numPaths*sizeof(long) + numPoints*sizeof(double)*2;
		// Allocate memory as necessary
		if (this->fgdbApiShapeBuffer->allocatedLength != totBytes)
			this->fgdbApiShapeBuffer->Allocate(totBytes);

		// Copy the shape type
		long shapeType = pgon->ShapeType;
		memcpy(this->fgdbApiShapeBuffer->shapeBuffer, &shapeType, sizeof(shapeType));
		long offset = sizeof(shapeType);

		WKPolygonHeader header = {
			pgon->Extent->XMin,
			pgon->Extent->YMin,
			pgon->Extent->XMax,
			pgon->Extent->YMax,
			numPaths,
			numPoints
		};

		memcpy(this->fgdbApiShapeBuffer->shapeBuffer+offset, &header, sizeof(WKPolygonHeader));
		offset += sizeof(WKPolygonHeader);
		
		long pathIdx = 0;
		long pointIdx = 0;
		double x,y;
		for (long i=0; i<numPaths; i++) {
			// Copy the part index
			memcpy(this->fgdbApiShapeBuffer->shapeBuffer+offset+i*4, &pathIdx, sizeof(pathIdx));

			// Copy the points for this part
			for (long j=0; j<pgon->Paths[i]->Length; j++) {
				x = pgon->Paths[i][j]->X;
				y = pgon->Paths[i][j]->Y;

				memcpy(this->fgdbApiShapeBuffer->shapeBuffer+offset+numPaths*4+pointIdx, &x, sizeof(x));
				pointIdx += 8;
				memcpy(this->fgdbApiShapeBuffer->shapeBuffer+offset+numPaths*4+pointIdx, &y, sizeof(y));
				pointIdx += 8;
			}

			pathIdx += pgon->Paths[i]->Length;
		}

		this->fgdbApiShapeBuffer->inUseLength = totBytes;
	}

	void ShapeBufferNet::SetMultiPoint(MultiPointNet^ mp) 
	{
		long numPoints = mp->NumPoints;
		long szLong = sizeof(long);
		long szMP = sizeof(WKMultiPointHeader);
		long szPt = sizeof(WKPoint);
		long szEnv = sizeof(WKEnvelope);
		long szPts = numPoints * sizeof(WKPoint);
		long totBytes1 = szLong + szMP + szPts;
		long totBytes = sizeof(long) + sizeof(WKMultiPointHeader) + numPoints * sizeof(WKPoint);
		// Allocate memory as necessary
		if (this->fgdbApiShapeBuffer->allocatedLength != totBytes)
			this->fgdbApiShapeBuffer->Allocate(totBytes);

		long shapeType = mp->ShapeType;
		memcpy(this->fgdbApiShapeBuffer->shapeBuffer, &shapeType, sizeof(shapeType));
		long offset = sizeof(shapeType);

		WKMultiPointHeader header = {
			mp->Extent->XMin,
			mp->Extent->YMin,
			mp->Extent->XMax,
			mp->Extent->YMax,
			numPoints
		};

		memcpy(this->fgdbApiShapeBuffer->shapeBuffer+offset, &header, sizeof(WKMultiPointHeader));
		offset += sizeof(WKMultiPointHeader);

		double x,y;
		for (long i=0; i<numPoints; i++) {
			x = mp->Points[i]->X;
			y = mp->Points[i]->Y;

			memcpy(this->fgdbApiShapeBuffer->shapeBuffer+offset, &x, sizeof(x));
			offset += 8;
			memcpy(this->fgdbApiShapeBuffer->shapeBuffer+offset, &y, sizeof(y));
			offset += 8;
		}

		this->fgdbApiShapeBuffer->inUseLength = totBytes;
	}
}