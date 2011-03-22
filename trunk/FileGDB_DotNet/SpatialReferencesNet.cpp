/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#include "stdafx.h"

#include "SpatialReferencesNet.h"
#include "Marshal.h"

namespace FileGDB_DotNet 
{
	SpatialReferenceInfoNet^ EnumSpatialReferenceInfoNet::NextGeographicSpatialReference()
	{
		FileGDBAPI::SpatialReferenceInfo spatialReferenceInfo;
		if (!this->fgdbApiEnumSpatialReferenceInfo->NextGeographicSpatialReference(spatialReferenceInfo))
			return nullptr;

		SpatialReferenceInfoNet^ outsr = gcnew SpatialReferenceInfoNet();
		outsr->auth_name = gcnew String(spatialReferenceInfo.auth_name.c_str());
		outsr->auth_srid = spatialReferenceInfo.auth_srid;
		outsr->srtext = gcnew String(spatialReferenceInfo.srtext.c_str());
		outsr->srname = gcnew String(spatialReferenceInfo.srname.c_str());

		return outsr;
	}

	SpatialReferenceInfoNet^ EnumSpatialReferenceInfoNet::NextProjectedSpatialReference()
	{
		FileGDBAPI::SpatialReferenceInfo spatialReferenceInfo;
		if (!this->fgdbApiEnumSpatialReferenceInfo->NextProjectedSpatialReference(spatialReferenceInfo))
			return nullptr;

		SpatialReferenceInfoNet^ outsr = gcnew SpatialReferenceInfoNet();
		outsr->auth_name = gcnew String(spatialReferenceInfo.auth_name.c_str());
		outsr->auth_srid = spatialReferenceInfo.auth_srid;
		outsr->srtext = gcnew String(spatialReferenceInfo.srtext.c_str());
		outsr->srname = gcnew String(spatialReferenceInfo.srname.c_str());

		return outsr;
	}

	void EnumSpatialReferenceInfoNet::Reset()
	{
		this->fgdbApiEnumSpatialReferenceInfo->Reset();
	}

	namespace SpatialReferences
	{
		/// Returns information about a spatial reference given its AUTH_SRID.
		SpatialReferenceInfoNet^ FindSpatialReferenceBySRID(int auth_srid)
		{
			FileGDBAPI::SpatialReferenceInfo spatialReferenceInfo;
			if (!FileGDBAPI::SpatialReferences::FindSpatialReferenceBySRID(auth_srid, spatialReferenceInfo))
				return nullptr;

			SpatialReferenceInfoNet^ outsr = gcnew SpatialReferenceInfoNet();
			outsr->auth_name = gcnew String(spatialReferenceInfo.auth_name.c_str());
			outsr->auth_srid = spatialReferenceInfo.auth_srid;
			outsr->srtext = gcnew String(spatialReferenceInfo.srtext.c_str());
			outsr->srname = gcnew String(spatialReferenceInfo.srname.c_str());

			return outsr;
		}

		/// Returns information about a spatial reference given its name.
		SpatialReferenceInfoNet^ FindSpatialReferenceByName(String^ cname)
		{
			std::wstring wcname;
			MarshalString(cname, wcname);

			FileGDBAPI::SpatialReferenceInfo spatialReferenceInfo;
			if (!FileGDBAPI::SpatialReferences::FindSpatialReferenceByName(wcname, spatialReferenceInfo))
				return nullptr;

			SpatialReferenceInfoNet^ outsr = gcnew SpatialReferenceInfoNet();
			outsr->auth_name = gcnew String(spatialReferenceInfo.auth_name.c_str());
			outsr->auth_srid = spatialReferenceInfo.auth_srid;
			outsr->srtext = gcnew String(spatialReferenceInfo.srtext.c_str());
			outsr->srname = gcnew String(spatialReferenceInfo.srname.c_str());

			return outsr;
		}
	};
}