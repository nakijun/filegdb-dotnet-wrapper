/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#pragma once

#define EXT_FILEGDB_API _declspec(dllimport)
#pragma warning (disable : 4251)

#include "FileGDBAPI.h"

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

		virtual ~EnvelopeNet() 
		{
			delete this->fgdbApiEnvelope;
		}

		FileGDBAPI::Envelope* fgdbApiEnvelope;

		bool IsEmpty();
		void SetEmpty();

		property double XMin 
		{
			double get() { return this->fgdbApiEnvelope->xMin; }
			void set(double value) { this->fgdbApiEnvelope->xMin = value; }
		}

		property double YMin 
		{
			double get() { return this->fgdbApiEnvelope->yMin; }
			void set(double value) { this->fgdbApiEnvelope->yMin = value; }
		}

		property double XMax 
		{
			double get() { return this->fgdbApiEnvelope->xMax; }
			void set(double value) { this->fgdbApiEnvelope->xMax = value; }
		}

		property double YMax 
		{
			double get() { return this->fgdbApiEnvelope->yMax; }
			void set(double value) { this->fgdbApiEnvelope->yMax = value; }
		}

	protected:
		!EnvelopeNet() {
			delete this->fgdbApiEnvelope;
		}
	};
}