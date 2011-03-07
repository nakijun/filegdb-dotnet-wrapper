/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#include "stdafx.h"

#include "PolygonNet.h"

namespace FileGDB_DotNet 
{
	void PolygonNet::UpdateExtent() 
	{
		this->Extent->XMin = Double::MaxValue;
		this->Extent->XMax = Double::MinValue;
		this->Extent->YMin = Double::MaxValue;
		this->Extent->YMax = Double::MinValue;

		for (int i=0; i<this->Paths->Length; i++) {
			for (int j=0; j<this->Paths[i]->Length; j++) {
				this->Extent->XMin = Math::Min(this->Paths[i][j]->X, this->Extent->XMin);
				this->Extent->XMax = Math::Max(this->Paths[i][j]->X, this->Extent->XMax);
				this->Extent->YMin = Math::Min(this->Paths[i][j]->Y, this->Extent->YMin);
				this->Extent->YMax = Math::Max(this->Paths[i][j]->Y, this->Extent->YMax);
			}
		}
	}
}