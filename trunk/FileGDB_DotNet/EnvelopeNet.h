/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#pragma once

#define EXT_FILEGDB_API _declspec(dllimport)
#pragma warning (disable : 4251)

#include "FileGDB_API_1_0_beta2/include/FileGDBAPI.h"

using namespace std;
using namespace System;

namespace FileGDB_DotNet 
{
	public ref class EnvelopeNet
	{
	public:
		EnvelopeNet() : fgdbApiEnvelope(new FileGDBAPI::Envelope) {}

		EnvelopeNet(double xmin, double xmax, double ymin, double ymax)
			: fgdbApiEnvelope(new FileGDBAPI::Envelope(xmin, xmax, ymin, ymax))
		{
		}

		~EnvelopeNet() 
		{
			delete fgdbApiEnvelope;
		}

		FileGDBAPI::Envelope* fgdbApiEnvelope;

		bool IsEmpty();
		void SetEmpty();

		property double xMin 
		{
			double get() { return fgdbApiEnvelope->xMin; }
			void set(double value) { fgdbApiEnvelope->xMin = value; }
		}

		property double yMin 
		{
			double get() { return fgdbApiEnvelope->yMin; }
			void set(double value) { fgdbApiEnvelope->yMin = value; }
		}

		property double xMax 
		{
			double get() { return fgdbApiEnvelope->xMax; }
			void set(double value) { fgdbApiEnvelope->xMax = value; }
		}

		property double yMax 
		{
			double get() { return fgdbApiEnvelope->yMax; }
			void set(double value) { fgdbApiEnvelope->yMax = value; }
		}

	protected:
		!EnvelopeNet() {
			delete fgdbApiEnvelope;
		}
	};
}