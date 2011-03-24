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
	public ref class ByteArrayNet
	{
	public:
		ByteArrayNet() : fgdbApiByteArray(new FileGDBAPI::ByteArray()) { this->m_bytes = nullptr; };
		ByteArrayNet(size_t length) : fgdbApiByteArray(new FileGDBAPI::ByteArray(length)) { this->m_bytes = nullptr; };

		virtual ~ByteArrayNet() 
		{
			delete this->fgdbApiByteArray;

			if (this->m_bytes != nullptr)
				this->m_bytes->Close();
		}

		FileGDBAPI::ByteArray* fgdbApiByteArray;
		

		bool Allocate(size_t length);
		void CommitBytes();

		property size_t AllocatedLength
		{
			size_t get() { return this->fgdbApiByteArray->allocatedLength; }
			void set(size_t value) { this->fgdbApiByteArray->allocatedLength = value; }
		}

		property size_t InUseLength
		{
			size_t get() { return this->fgdbApiByteArray->inUseLength; }
			void set(size_t value) { this->fgdbApiByteArray->inUseLength = value; }
		}

		/// <summary>
        ///   Returns the raw bytes as a memory stream
        /// </summary>
		property MemoryStream^ Bytes
		{
			MemoryStream^ get() {
				if (this->m_bytes == nullptr) {
					this->m_bytes = gcnew MemoryStream((int)this->fgdbApiByteArray->allocatedLength);
					// Read in the bytes
					for (unsigned long i=0; i<this->fgdbApiByteArray->inUseLength; i++) {
						this->m_bytes->WriteByte(*(this->fgdbApiByteArray->byteArray+i));
					}
					this->m_bytes->Seek(0, SeekOrigin::Begin);
				}

				return this->m_bytes;
			}
		}

	private:
		MemoryStream^ m_bytes;

	protected:
		!ByteArrayNet() {
			delete this->fgdbApiByteArray;

			if (this->m_bytes != nullptr)
				this->m_bytes->Close();}
	};
}