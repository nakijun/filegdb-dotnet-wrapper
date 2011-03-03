/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#include "stdafx.h"

#include "ShapeBufferNet.h"

namespace FileGDB_DotNet 
{
	struct WKPoint {
		double x;
		double y;
	};

	struct WKEnvelope {
		double xmin;
		double xmax;
		double ymin;
		double ymax;
	};

	bool ShapeBufferNet::Allocate(unsigned long length)
	{
		return fgdbApiShapeBuffer->Allocate(length);
	}

	int ShapeBufferNet::GetShapeType() 
	{
		return *((long*)fgdbApiShapeBuffer->shapeBuffer);
	}

	/// <summary>
	/// Returns the .NET representation of the geometry found
	/// in the ShapeBuffer.
	/// </summary>
	GeometryNet^ ShapeBufferNet::GetGeometry() 
	{
		long shpType = GetShapeType();

		if (shpType == 1) {
			return GetPoint();
		} else if (shpType == 3) {
			return GetPolyline();
		} else if (shpType == 5) {
			return GetPolygon();
		} else if (shpType == 8) {
			return GetMultipoint();
		} else {
			// Unsupported shape type
			return nullptr;
		}
		
	}

	PointNet^ ShapeBufferNet::GetPoint()
	{
		BYTE* sb = fgdbApiShapeBuffer->shapeBuffer;
		WKPoint* pt = (WKPoint*)(sb+4);
		return gcnew PointNet((*pt).x, (*pt).y);
	}

	PolylineNet^ ShapeBufferNet::GetPolyline()
	{
		BYTE* sb = fgdbApiShapeBuffer->shapeBuffer;
		PolylineNet^ pl = gcnew PolylineNet();
		
		WKEnvelope* extent = (WKEnvelope*)(sb+4);
		pl->Extent->xMin = (*extent).xmin;
		pl->Extent->yMin = (*extent).ymin;
		pl->Extent->xMax = (*extent).xmax;
		pl->Extent->yMax = (*extent).ymax;

		pl->NumParts = *((int*)(sb+36));
		pl->NumPoints = *((int*)(sb+40));

		int* parts = (int*)(sb+44);
		WKPoint* points = (WKPoint*)(sb+44+pl->NumParts*4);

		pl->Parts = gcnew array<array<PointNet^>^>(pl->NumParts);
		int totPoints = 0;
		for (int i=0; i<pl->NumParts; i++) {
			if (i < pl->NumParts-1) {
				// Total points is the next part index minus current part index
				totPoints = *(parts+i+1) - *(parts+i);
			} else {
				// No next part index, use total # of points in the array minus current part idx
				totPoints = pl->NumPoints - *(parts+i);
			}

			pl->Parts[i] = gcnew array<PointNet^>(totPoints);
			for (int j=0; j<totPoints; j++) {
				pl->Parts[i][j] = gcnew PointNet((*points).x, (*points).y);
				points++;
			}
		}

		return pl;
	}

	PolygonNet^ ShapeBufferNet::GetPolygon()
	{
		BYTE* sb = fgdbApiShapeBuffer->shapeBuffer;
		PolygonNet^ pg = gcnew PolygonNet();
		
		WKEnvelope* extent = (WKEnvelope*)(sb+4);
		pg->Extent->xMin = (*extent).xmin;
		pg->Extent->yMin = (*extent).ymin;
		pg->Extent->xMax = (*extent).xmax;
		pg->Extent->yMax = (*extent).ymax;

		pg->NumPaths = *((int*)(sb+36));
		pg->NumPoints = *((int*)(sb+40));

		int* paths = (int*)(sb+44);
		WKPoint* points = (WKPoint*)(sb+44+pg->NumPaths*4);

		pg->Paths = gcnew array<array<PointNet^>^>(pg->NumPaths);
		int totPoints = 0;
		for (int i=0; i<pg->NumPaths; i++) {
			if (i < pg->NumPaths-1) {
				// Total points is the next path index minus current path index
				totPoints = *(paths+i+1) - *(paths+i);
			} else {
				// No next path index, use total # of points in the array minus current path idx
				totPoints = pg->NumPoints - *(paths+i);
			}

			pg->Paths[i] = gcnew array<PointNet^>(totPoints);
			for (int j=0; j<totPoints; j++) {
				pg->Paths[i][j] = gcnew PointNet((*points).x, (*points).y);
				points++;
			}
		}

		return pg;
	}

	MultiPointNet^ ShapeBufferNet::GetMultipoint()
	{
		BYTE* sb = fgdbApiShapeBuffer->shapeBuffer;
		MultiPointNet^ mp = gcnew MultiPointNet();
		
		WKEnvelope* extent = (WKEnvelope*)(sb+4);
		mp->Extent->xMin = (*extent).xmin;
		mp->Extent->yMin = (*extent).ymin;
		mp->Extent->xMax = (*extent).xmax;
		mp->Extent->yMax = (*extent).ymax;

		mp->NumPoints = *((int*)(sb+36));

		WKPoint* points = (WKPoint*)(sb+40);

		mp->Points = gcnew array<PointNet^>(mp->NumPoints);
		int totPoints = 0;
		for (int i=0; i<mp->NumPoints; i++) {
			mp->Points[i] = gcnew PointNet((*points).x, (*points).y);
			points++;
		}

		return mp;
	}
}