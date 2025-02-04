/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#include "stdafx.h"

#include "RowNet.h"
#include "PointShapeBufferNet.h"
#include "MultiPointShapeBufferNet.h"
#include "MultiPartShapeBufferNet.h"
#include "MultiPatchShapeBufferNet.h"
#include "FGDBException.h"

namespace FileGDB_DotNet 
{
	bool RowNet::IsNull(String^ field) 
	{
		std::wstring wField;
		MarshalString(field, wField);
		
		bool val;
		fgdbError hr;
		if ((hr = this->fgdbApiRow->IsNull(wField, val)) != S_OK) {
			throw gcnew FGDBException("Error getting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return val;
	}

	void RowNet::SetNull(String^ field) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		fgdbError hr;
		if ((hr = this->fgdbApiRow->SetNull(wField)) != S_OK) {
			throw gcnew FGDBException("Error setting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	long RowNet::GetOID() 
	{
		int32 val;
		fgdbError hr;
		if ((hr = this->fgdbApiRow->GetOID(val)) != S_OK) {
			throw gcnew FGDBException("Error getting OID.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return val;
	}

	System::Guid^ RowNet::GetGlobalID() 
	{
		FileGDBAPI::Guid val;
		fgdbError hr;
		if ((hr = this->fgdbApiRow->GetGlobalID(val)) != S_OK) {
			throw gcnew Exception("Error getting Global ID.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")");
		}

		return MarshalGuid(val);
	}

	ShapeBufferNet^ RowNet::GetGeometry() 
	{
		FileGDBAPI::ShapeBuffer* sb = new FileGDBAPI::ShapeBuffer;
		fgdbError hr;
		if ((hr = this->fgdbApiRow->GetGeometry(*sb)) != S_OK) {
			throw gcnew FGDBException("Error getting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		FileGDBAPI::ShapeType shapeType;
		sb->GetShapeType(shapeType);

		ShapeBufferNet^ outsb;
		// Create the appropriate class based on the shape type
		switch (shapeType) {
			case FileGDBAPI::shapeGeneralPoint:
			case FileGDBAPI::shapePoint:
			case FileGDBAPI::shapePointM:
			case FileGDBAPI::shapePointZ:
			case FileGDBAPI::shapePointZM:
				outsb = gcnew PointShapeBufferNet();
				break;
			case FileGDBAPI::shapeGeneralMultipoint:
			case FileGDBAPI::shapeMultipoint:
			case FileGDBAPI::shapeMultipointM:
			case FileGDBAPI::shapeMultipointZ:
			case FileGDBAPI::shapeMultipointZM:
				outsb = gcnew MultiPointShapeBufferNet();
				break;
			case FileGDBAPI::shapeGeneralPolyline:
			case FileGDBAPI::shapePolyline:
			case FileGDBAPI::shapePolylineM:
			case FileGDBAPI::shapePolylineZ:
			case FileGDBAPI::shapePolylineZM:
			case FileGDBAPI::shapeGeneralPolygon:
			case FileGDBAPI::shapePolygon:
			case FileGDBAPI::shapePolygonM:
			case FileGDBAPI::shapePolygonZ:
			case FileGDBAPI::shapePolygonZM:
				outsb = gcnew MultiPartShapeBufferNet();
				break;
			case FileGDBAPI::shapeMultiPatch:
			case FileGDBAPI::shapeMultiPatchM:
			case FileGDBAPI::shapeGeneralMultiPatch:
				outsb = gcnew MultiPatchShapeBufferNet();
				break;
			default:
				outsb = gcnew ShapeBufferNet();
				break;
		};

		// Delete the internal buffer pointer and assign it to the one created earlier
		delete outsb->fgdbApiShapeBuffer;
		outsb->fgdbApiShapeBuffer = sb;

		return outsb;
	}

	void RowNet::SetGeometry(ShapeBufferNet^ val) 
	{
		fgdbError hr;
		if ((hr = this->fgdbApiRow->SetGeometry(*val->fgdbApiShapeBuffer)) != S_OK) {
			throw gcnew FGDBException("Error setting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	short RowNet::GetShort(String^ field) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		short val;
		fgdbError hr;
		if ((hr = this->fgdbApiRow->GetShort(wField, val)) != S_OK) {
			throw gcnew FGDBException("Error getting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return val;
	}

	void RowNet::SetShort(String^ field, short val) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		fgdbError hr;
		if ((hr = this->fgdbApiRow->SetShort(wField, val)) != S_OK) {
			throw gcnew FGDBException("Error setting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	int32 RowNet::GetInteger(String^ field) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		int32 val;
		fgdbError hr;
		if ((hr = this->fgdbApiRow->GetInteger(wField, val)) != S_OK) {
			throw gcnew FGDBException("Error getting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return val;
	}

	void RowNet::SetInteger(String^ field, int32 val) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		fgdbError hr;
		if ((hr = this->fgdbApiRow->SetInteger(wField, val)) != S_OK) {
			throw gcnew FGDBException("Error setting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	float RowNet::GetFloat(String^ field) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		float val;
		fgdbError hr;
		if ((hr = this->fgdbApiRow->GetFloat(wField, val)) != S_OK) {
			throw gcnew FGDBException("Error getting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return val;
	}

	void RowNet::SetFloat(String^ field, float val) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		fgdbError hr;
		if ((hr = this->fgdbApiRow->SetFloat(wField, val)) != S_OK) {
			throw gcnew FGDBException("Error setting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	double RowNet::GetDouble(String^ field) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		double val;
		fgdbError hr;
		if ((hr = this->fgdbApiRow->GetDouble(wField, val)) != S_OK) {
			throw gcnew FGDBException("Error getting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return val;
	}

	void RowNet::SetDouble(String^ field, double val) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		fgdbError hr;
		if ((hr = this->fgdbApiRow->SetDouble(wField, val)) != S_OK) {
			throw gcnew FGDBException("Error setting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	System::DateTime^ RowNet::GetDate(String^ field) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		struct tm val;
		fgdbError hr;
		if ((hr = this->fgdbApiRow->GetDate(wField, val)) != S_OK) {
			throw gcnew FGDBException("Error getting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return MarshalDateTime(val);
	}

	void RowNet::SetDate(String^ field, System::DateTime val) 
	{
		std::wstring wField;
		MarshalString(field, wField);
		struct tm dtval = MarshalDateTime(val);

		fgdbError hr;
		if ((hr = this->fgdbApiRow->SetDate(wField, dtval)) != S_OK) {
			throw gcnew FGDBException("Error setting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	String^ RowNet::GetString(String^ field) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		std::wstring val;
		fgdbError hr;
		if ((hr = this->fgdbApiRow->GetString(wField, val)) != S_OK) {
			throw gcnew FGDBException("Error getting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		String^ retval = gcnew String(val.c_str());
		return retval;
	}

	void RowNet::SetString(String^ field, String^ val) 
	{
		std::wstring wField, wVal;
		MarshalString(field, wField);
		MarshalString(val, wVal);

		fgdbError hr;
		if ((hr = this->fgdbApiRow->SetString(wField, wVal)) != S_OK) {
			throw gcnew FGDBException("Error setting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	Guid^ RowNet::GetGUID(String^ field) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		FileGDBAPI::Guid val;
		fgdbError hr;
		if ((hr = this->fgdbApiRow->GetGUID(wField, val)) != S_OK) {
			throw gcnew FGDBException("Error getting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return MarshalGuid(val);
	}

	void RowNet::SetGUID(String^ field, Guid val) 
	{
		std::wstring wField;
		MarshalString(field, wField);
		FileGDBAPI::Guid guidval = MarshalGuid(val);

		fgdbError hr;
		if ((hr = this->fgdbApiRow->SetGUID(wField, guidval)) != S_OK) {
			throw gcnew FGDBException("Error setting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	String^ RowNet::GetXML(String^ field) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		std::string val;
		fgdbError hr;
		if ((hr = this->fgdbApiRow->GetXML(wField, val)) != S_OK) {
			throw gcnew FGDBException("Error getting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		String^ retval = gcnew String(val.c_str());
		return retval;
	}

	void RowNet::SetXML(String^ field, String^ val) 
	{
		std::wstring wField;
		std::string sVal;
		MarshalString(field, wField);
		MarshalString(val, sVal);

		fgdbError hr;
		if ((hr = this->fgdbApiRow->SetXML(wField, sVal)) != S_OK) {
			throw gcnew FGDBException("Error setting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	RasterNet^ RowNet::GetRaster(String^ field) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		RasterNet^ outraster = gcnew RasterNet();
		fgdbError hr;
		if ((hr = this->fgdbApiRow->GetRaster(wField, *outraster->fgdbApiRaster)) != S_OK) {
			throw gcnew FGDBException("Error getting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return outraster;
	}

	void RowNet::SetRaster(String^ field, RasterNet^ val) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		fgdbError hr;
		if ((hr = this->fgdbApiRow->SetRaster(wField, *val->fgdbApiRaster)) != S_OK) {
			throw gcnew FGDBException("Error setting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	ByteArrayNet^ RowNet::GetBinary(String^ field) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		ByteArrayNet^ outba = gcnew ByteArrayNet();
		fgdbError hr;
		if ((hr = this->fgdbApiRow->GetBinary(wField, *outba->fgdbApiByteArray)) != S_OK) {
			throw gcnew FGDBException("Error getting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return outba;
	}

	void RowNet::SetBinary(String^ field, ByteArrayNet^ val) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		fgdbError hr;
		if ((hr = this->fgdbApiRow->SetBinary(wField, *val->fgdbApiByteArray)) != S_OK) {
			throw gcnew FGDBException("Error setting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}
}