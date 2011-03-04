/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#pragma once

#define EXT_FILEGDB_API _declspec(dllimport)
#pragma warning (disable : 4251)

#include "FileGDB_API_1_0_beta2/include/FileGDBAPI.h"

#include "GeometryNet.h"
#include "PointNet.h"
#include "PolylineNet.h"
#include "PolygonNet.h"
#include "MultiPointNet.h"

using namespace std;
using namespace System;
using namespace Runtime::InteropServices;

namespace FileGDB_DotNet 
{
	public ref class ShapeBufferNet
	{
	public:
		ShapeBufferNet() : fgdbApiShapeBuffer(new FileGDBAPI::ShapeBuffer()) {};
		ShapeBufferNet(unsigned long length) : fgdbApiShapeBuffer(new FileGDBAPI::ShapeBuffer(length)) {};

		~ShapeBufferNet() 
		{
			delete fgdbApiShapeBuffer;
		}

		FileGDBAPI::ShapeBuffer* fgdbApiShapeBuffer;

	private:
		PointNet^ GetPoint();
		PolylineNet^ GetPolyline();
		PolygonNet^ GetPolygon();
		MultiPointNet^ GetMultipoint();
		
		void ShapeBufferNet::SetPoint(PointNet^ point);
		void ShapeBufferNet::SetPolyline(PolylineNet^ pline);
		void ShapeBufferNet::SetPolygon(PolygonNet^ pgon);

	public:
		long GetShapeType();
		GeometryNet^ GetGeometry();
		void SetGeometry(GeometryNet^ geometry);

		bool Allocate(unsigned long length);

		property unsigned long allocatedLength
		{
			unsigned long get() { return fgdbApiShapeBuffer->allocatedLength; }
			void set(unsigned long value) { fgdbApiShapeBuffer->allocatedLength = value; }
		}

		property unsigned long inUseLength
		{
			unsigned long get() { return fgdbApiShapeBuffer->inUseLength; }
			void set(unsigned long value) { fgdbApiShapeBuffer->inUseLength = value; }
		}

	protected:
		!ShapeBufferNet() {
			delete fgdbApiShapeBuffer;
		}
	};
}