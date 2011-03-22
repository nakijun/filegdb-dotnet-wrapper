/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#pragma once

#define EXT_FILEGDB_API _declspec(dllimport)
#pragma warning (disable : 4251)

#include "FileGDBAPI.h"

using namespace std;
using namespace System;
using namespace System::IO;
using namespace Runtime::InteropServices;

namespace FileGDB_DotNet 
{
	public value class SpatialReferenceInfoNet
	{
	public:
		// The name of the standard or standards body that is being cited for this reference system.
		String^ auth_name;
		// The ID of the Spatial Reference System as defined by the Authority cited in AUTH_NAME.
		int auth_srid;
		// The Well-known Text Representation of the Spatial Reference System.
		String^ srtext;
		// The name of the Spatial Reference System.
		String^ srname;
	};

	public ref class EnumSpatialReferenceInfoNet
	{
	public:
		EnumSpatialReferenceInfoNet() : fgdbApiEnumSpatialReferenceInfo(new FileGDBAPI::EnumSpatialReferenceInfo()) {};
		
		virtual ~EnumSpatialReferenceInfoNet() 
		{
			delete this->fgdbApiEnumSpatialReferenceInfo;
		}

		SpatialReferenceInfoNet^ NextGeographicSpatialReference();
		SpatialReferenceInfoNet^ NextProjectedSpatialReference();
		void Reset();

	private:
		FileGDBAPI::EnumSpatialReferenceInfo* fgdbApiEnumSpatialReferenceInfo;

	protected:
		!EnumSpatialReferenceInfoNet() {
			delete this->fgdbApiEnumSpatialReferenceInfo;
		}
	};
}