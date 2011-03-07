/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#include "stdafx.h"

#include "PolylineNet.h"

namespace FileGDB_DotNet 
{
	void PolylineNet::UpdateExtent() 
	{
		this->Extent->XMin = Double::MaxValue;
		this->Extent->XMax = Double::MinValue;
		this->Extent->YMin = Double::MaxValue;
		this->Extent->YMax = Double::MinValue;

		for (int i=0; i<this->Parts->Length; i++) {
			for (int j=0; j<this->Parts[i]->Length; j++) {
				this->Extent->XMin = Math::Min(this->Parts[i][j]->X, this->Extent->XMin);
				this->Extent->XMax = Math::Max(this->Parts[i][j]->X, this->Extent->XMax);
				this->Extent->YMin = Math::Min(this->Parts[i][j]->Y, this->Extent->YMin);
				this->Extent->YMax = Math::Max(this->Parts[i][j]->Y, this->Extent->YMax);
			}
		}
	}
}