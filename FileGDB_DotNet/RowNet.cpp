// This is the main DLL file.

#include "stdafx.h"

#include "RowNet.h"
#include "FGDBException.h"

namespace FileGDB_DotNet 
{
	bool RowNet::IsNull(String^ field) 
	{
		std::wstring wField;
		MarshalString(field, wField);
		
		bool val;
		long hr;
		if ((hr = fgdbApiRow->IsNull(wField, val)) != S_OK) {
			throw gcnew FGDBException("Error getting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return val;
	}

	void RowNet::SetNull(String^ field) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		long hr;
		if ((hr = fgdbApiRow->SetNull(wField)) != S_OK) {
			throw gcnew FGDBException("Error setting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	long RowNet::GetOID() 
	{
		long val;
		long hr;
		if ((hr = fgdbApiRow->GetOID(val)) != S_OK) {
			throw gcnew FGDBException("Error getting OID.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return val;
	}

	System::Guid^ RowNet::GetGlobalID() 
	{
		GUID val;
		long hr;
		if ((hr = fgdbApiRow->GetGlobalID(val)) != S_OK) {
			throw gcnew Exception("Error getting Global ID.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")");
		}

		return MarshalGuid(val);
	}

	ShapeBufferNet^ RowNet::GetGeometry() 
	{
		FileGDBAPI::ShapeBuffer val;
		long hr;
		if ((hr = fgdbApiRow->GetGeometry(val)) != S_OK) {
			throw gcnew FGDBException("Error getting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		ShapeBufferNet^ outsb = gcnew ShapeBufferNet(val.allocatedLength);
		outsb->fgdbApiShapeBuffer = &val;
		return outsb;
	}

	void RowNet::SetGeometry(ShapeBufferNet^ val) 
	{
		long hr;
		if ((hr = fgdbApiRow->SetGeometry(*val->fgdbApiShapeBuffer)) != S_OK) {
			throw gcnew FGDBException("Error setting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	short RowNet::GetShort(String^ field) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		short val;
		long hr;
		if ((hr = fgdbApiRow->GetShort(wField, val)) != S_OK) {
			throw gcnew FGDBException("Error getting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return val;
	}

	void RowNet::SetShort(String^ field, short val) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		long hr;
		if ((hr = fgdbApiRow->SetShort(wField, val)) != S_OK) {
			throw gcnew FGDBException("Error setting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	long RowNet::GetInteger(String^ field) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		long val;
		long hr;
		if ((hr = fgdbApiRow->GetInteger(wField, val)) != S_OK) {
			throw gcnew FGDBException("Error getting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return val;
	}

	void RowNet::SetInteger(String^ field, long val) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		long hr;
		if ((hr = fgdbApiRow->SetInteger(wField, val)) != S_OK) {
			throw gcnew FGDBException("Error setting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	float RowNet::GetFloat(String^ field) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		float val;
		long hr;
		if ((hr = fgdbApiRow->GetFloat(wField, val)) != S_OK) {
			throw gcnew FGDBException("Error getting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return val;
	}

	void RowNet::SetFloat(String^ field, float val) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		long hr;
		if ((hr = fgdbApiRow->SetFloat(wField, val)) != S_OK) {
			throw gcnew FGDBException("Error setting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	double RowNet::GetDouble(String^ field) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		double val;
		long hr;
		if ((hr = fgdbApiRow->GetDouble(wField, val)) != S_OK) {
			throw gcnew FGDBException("Error getting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return val;
	}

	void RowNet::SetDouble(String^ field, double val) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		long hr;
		if ((hr = fgdbApiRow->SetDouble(wField, val)) != S_OK) {
			throw gcnew FGDBException("Error setting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	System::DateTime^ RowNet::GetDate(String^ field) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		struct tm val;
		long hr;
		if ((hr = fgdbApiRow->GetDate(wField, val)) != S_OK) {
			throw gcnew FGDBException("Error getting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return MarshalDateTime(val);
	}

	void RowNet::SetDate(String^ field, System::DateTime val) 
	{
		std::wstring wField;
		MarshalString(field, wField);
		struct tm dtval = MarshalDateTime(val);

		long hr;
		if ((hr = fgdbApiRow->SetDate(wField, dtval)) != S_OK) {
			throw gcnew FGDBException("Error setting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	String^ RowNet::GetString(String^ field) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		std::wstring val;
		long hr;
		if ((hr = fgdbApiRow->GetString(wField, val)) != S_OK) {
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

		long hr;
		if ((hr = fgdbApiRow->SetString(wField, wVal)) != S_OK) {
			throw gcnew FGDBException("Error setting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	Guid^ RowNet::GetGUID(String^ field) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		GUID val;
		long hr;
		if ((hr = fgdbApiRow->GetGUID(wField, val)) != S_OK) {
			throw gcnew FGDBException("Error getting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		return MarshalGuid(val);
	}

	void RowNet::SetGUID(String^ field, Guid val) 
	{
		std::wstring wField;
		MarshalString(field, wField);
		GUID guidval = MarshalGuid(val);

		long hr;
		if ((hr = fgdbApiRow->SetGUID(wField, guidval)) != S_OK) {
			throw gcnew FGDBException("Error setting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	String^ RowNet::GetXML(String^ field) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		std::string val;
		long hr;
		if ((hr = fgdbApiRow->GetXML(wField, val)) != S_OK) {
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

		long hr;
		if ((hr = fgdbApiRow->SetXML(wField, sVal)) != S_OK) {
			throw gcnew FGDBException("Error setting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	RasterNet^ RowNet::GetRaster(String^ field) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		FileGDBAPI::Raster val;
		long hr;
		if ((hr = fgdbApiRow->GetRaster(wField, val)) != S_OK) {
			throw gcnew FGDBException("Error getting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		RasterNet^ outraster = gcnew RasterNet();
		outraster->fgdbApiRaster = &val;
		return outraster;
	}

	void RowNet::SetRaster(String^ field, RasterNet^ val) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		long hr;
		if ((hr = fgdbApiRow->SetRaster(wField, *val->fgdbApiRaster)) != S_OK) {
			throw gcnew FGDBException("Error setting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}

	ByteArrayNet^ RowNet::GetBinary(String^ field) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		FileGDBAPI::ByteArray val;
		long hr;
		if ((hr = fgdbApiRow->GetBinary(wField, val)) != S_OK) {
			throw gcnew FGDBException("Error getting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}

		ByteArrayNet^ outba = gcnew ByteArrayNet(val.allocatedLength);
		outba->fgdbApiByteArray = &val;
		return outba;
	}

	void RowNet::SetBinary(String^ field, ByteArrayNet^ val) 
	{
		std::wstring wField;
		MarshalString(field, wField);

		long hr;
		if ((hr = fgdbApiRow->SetBinary(wField, *val->fgdbApiByteArray)) != S_OK) {
			throw gcnew FGDBException("Error setting value.  Error code: " + hr + "  (0x" + hr.ToString("X8") + ")", hr);
		}
	}
}