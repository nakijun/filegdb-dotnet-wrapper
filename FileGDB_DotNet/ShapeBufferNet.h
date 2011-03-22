/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#pragma once

#define EXT_FILEGDB_API _declspec(dllimport)
#pragma warning (disable : 4251)

#include "FileGDBAPI.h"

#include "GeometryNet.h"
#include "PointNet.h"
#include "PolylineNet.h"
#include "PolygonNet.h"
#include "MultiPointNet.h"

using namespace std;
using namespace System;
using namespace System::IO;
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
			delete this->fgdbApiShapeBuffer;

			if (this->m_bytes != nullptr)
				this->m_bytes->Close();
		}

		FileGDBAPI::ShapeBuffer* fgdbApiShapeBuffer;

	private:
		PointNet^ GetPoint();
		PolylineNet^ GetPolyline();
		PolygonNet^ GetPolygon();
		MultiPointNet^ GetMultipoint();
		
		void SetPoint(PointNet^ point);
		void SetPolyline(PolylineNet^ pline);
		void SetPolygon(PolygonNet^ pgon);
		void SetMultiPoint(MultiPointNet^ mp) ;

	public:
		long GetShapeType();
		GeometryNet^ GetGeometry();
		void SetGeometry(GeometryNet^ geometry);

		bool Allocate(unsigned long length);

		property unsigned long allocatedLength
		{
			unsigned long get() { return this->fgdbApiShapeBuffer->allocatedLength; }
			void set(unsigned long value) { this->fgdbApiShapeBuffer->allocatedLength = value; }
		}

		property unsigned long inUseLength
		{
			unsigned long get() { return this->fgdbApiShapeBuffer->inUseLength; }
			void set(unsigned long value) { this->fgdbApiShapeBuffer->inUseLength = value; }
		}

		/// <summary>
        ///   Returns the raw bytes as a memory stream
        /// </summary>
		property MemoryStream^ Bytes
		{
			MemoryStream^ get() {
				if (this->m_bytes == nullptr) {
					this->m_bytes = gcnew MemoryStream(this->fgdbApiShapeBuffer->allocatedLength);
					// Read in the bytes
					for (unsigned long i=0; i<this->fgdbApiShapeBuffer->inUseLength; i++) {
						this->m_bytes->WriteByte(*(this->fgdbApiShapeBuffer->shapeBuffer+i));
					}
					this->m_bytes->Seek(0, SeekOrigin::Begin);
				}

				return this->m_bytes;
			}
		}

	private:
		MemoryStream^ m_bytes;

	protected:
		!ShapeBufferNet() {
			delete this->fgdbApiShapeBuffer;

			if (this->m_bytes != nullptr)
				this->m_bytes->Close();
		}
	};
}