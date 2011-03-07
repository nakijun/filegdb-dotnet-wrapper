/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#pragma once

#include "GeometryNet.h"
#include "EnvelopeNet.h"
#include "PointNet.h"

namespace FileGDB_DotNet 
{
	public ref class MultiPointNet : GeometryNet
	{
	public:
		MultiPointNet() : GeometryNet(8)
		{
			this->Extent = gcnew EnvelopeNet();
			this->Points = nullptr;
		}

		EnvelopeNet^ Extent;
		array<PointNet^>^ Points;

		void UpdateExtent();

		property long NumPoints {
			long get() { 
				if (this->Points == nullptr) {
					return 0;
				} else {
					return this->Points->Length;
				}
			};
		}
	};
}