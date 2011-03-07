/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#include "stdafx.h"

#include "MultiPointNet.h"

namespace FileGDB_DotNet 
{
	void MultiPointNet::UpdateExtent() 
	{
		this->Extent->XMin = Double::MaxValue;
		this->Extent->XMax = Double::MinValue;
		this->Extent->YMin = Double::MaxValue;
		this->Extent->YMax = Double::MinValue;

		for (int i=0; i<this->Points->Length; i++) {
			this->Extent->XMin = Math::Min(this->Points[i]->X, this->Extent->XMin);
			this->Extent->XMax = Math::Max(this->Points[i]->X, this->Extent->XMax);
			this->Extent->YMin = Math::Min(this->Points[i]->Y, this->Extent->YMin);
			this->Extent->YMax = Math::Max(this->Points[i]->Y, this->Extent->YMax);
		}
	}
}