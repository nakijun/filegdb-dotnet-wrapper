/**
 * Copyright (c) 2011 Sasa Ivetic, Map It Out Inc.
 */


#include "stdafx.h"

#include "EnvelopeNet.h"
#include "FGDBException.h"

namespace FileGDB_DotNet 
{
	bool EnvelopeNet::IsEmpty() 
	{
		return this->fgdbApiEnvelope->IsEmpty();
	}

	void EnvelopeNet::SetEmpty()
	{
		this->fgdbApiEnvelope->SetEmpty();
	}
}