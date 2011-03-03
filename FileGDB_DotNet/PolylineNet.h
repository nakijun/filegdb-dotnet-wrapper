/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#pragma once

#include "GeometryNet.h"
#include "PointNet.h"
#include "EnvelopeNet.h"

namespace FileGDB_DotNet 
{
	public ref class PolylineNet : GeometryNet
	{
	public:
		PolylineNet() : GeometryNet(3)
		{
			this->Extent = gcnew EnvelopeNet();
			this->NumParts = 0;
			this->NumPoints = 0;
			this->Parts = nullptr;
		}

		EnvelopeNet^ Extent;
		int NumParts;
		int NumPoints;
		array<array<PointNet^>^>^ Parts;
	};
}