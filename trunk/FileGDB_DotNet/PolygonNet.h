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
			this->Paths = nullptr;
		}

		EnvelopeNet^ Extent;
		array<array<PointNet^>^>^ Paths;

		void UpdateExtent();

		property long NumPaths {
			long get() { 
				if (this->Paths == nullptr) {
					return 0;
				} else {
					return this->Paths->Length;
				}
			};
		}

		property long NumPoints {
			long get() { 
				if (this->Paths == nullptr) {
					return 0;
				} else {
					long pts = 0;
					for (long i=0; i<this->Paths->Length; i++) {
						if (this->Paths[i] != nullptr)
							pts += this->Paths[i]->Length;
					}

					return pts;
				}
			};
		}
	};
}