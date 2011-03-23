/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */


#pragma once

#define EXT_FILEGDB_API _declspec(dllimport)
#pragma warning (disable : 4251)

#include "FileGDBAPI.h"
#include "ConstantsNet.h"

using namespace std;
using namespace System;
using namespace System::IO;
using namespace Runtime::InteropServices;

namespace FileGDB_DotNet 
{
	public ref class PointNet
	{
	public:
		PointNet() { }

		PointNet(double x, double y)
		{
			this->x = x;
			this->y = y;
		}

		double x;
		double y;
	};

	public ref class ShapeBufferNet
	{
	public:
		ShapeBufferNet() : fgdbApiShapeBuffer(new FileGDBAPI::ShapeBuffer()) {};
		ShapeBufferNet(unsigned long length) : fgdbApiShapeBuffer(new FileGDBAPI::ShapeBuffer(length)) {};

		virtual ~ShapeBufferNet() 
		{
			delete this->fgdbApiShapeBuffer;

			if (this->m_bytes != nullptr)
				this->m_bytes->Close();
		}

		FileGDBAPI::ShapeBuffer* fgdbApiShapeBuffer;

		ShapeTypeNet GetShapeType();
		bool Allocate(unsigned long length);

		static bool HasZs(int shapeType);
		static bool HasMs(int shapeType);
		static bool HasIDs(int shapeType);
		static bool HasCurves(int shapeType);
		static bool HasNormals(int shapeType);
		static bool HasTextures(int shapeType);
		static bool HasMaterials(int shapeType);

		static int GeometryType(int shapeType);

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