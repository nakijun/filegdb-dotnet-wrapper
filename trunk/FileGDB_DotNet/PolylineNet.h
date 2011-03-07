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
			this->Parts = nullptr;
		}

		EnvelopeNet^ Extent;
		array<array<PointNet^>^>^ Parts;

		void UpdateExtent();

		property long NumParts {
			long get() { 
				if (this->Parts == nullptr) {
					return 0;
				} else {
					return this->Parts->Length;
				}
			};
		}

		property long NumPoints {
			long get() { 
				if (this->Parts == nullptr) {
					return 0;
				} else {
					long pts = 0;
					for (long i=0; i<this->Parts->Length; i++) {
						if (this->Parts[i] != nullptr)
							pts += this->Parts[i]->Length;
					}

					return pts;
				}
			};
		}
	};
}