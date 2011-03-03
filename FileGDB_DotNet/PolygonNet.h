/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#pragma once

#include "GeometryNet.h"
#include "EnvelopeNet.h"
#include "PointNet.h"

namespace FileGDB_DotNet 
{
	public ref class PolygonNet : GeometryNet
	{
	public:
		PolygonNet() : GeometryNet(5)
		{
			this->Extent = gcnew EnvelopeNet();
			this->NumPaths = 0;
			this->NumPoints = 0;
			this->Paths = nullptr;
		}

		EnvelopeNet^ Extent;
		int NumPaths;
		int NumPoints;
		array<array<PointNet^>^>^ Paths;
	};
}