/**
 * Code by Sasa Ivetic (Map It Out Inc.) 2011
 */

#include "stdafx.h"

#include "ByteArrayNet.h"

namespace FileGDB_DotNet 
{
	bool ByteArrayNet::Allocate(unsigned long length)
	{
		return this->fgdbApiByteArray->Allocate(length);
	}

	/// <summary>
	///   Commits changes made on the exposed MemoryStream
	///   object to the internal byte array.  Note: changes
	///   are only committed to the internal byte array,
	///   they are NOT saved to the FGDB.  To save the changes,
	///   RowNet::SetBinary must be called following the commit.
	/// </summary>
	void ByteArrayNet::CommitBytes()
	{
		// Do nothing in case the bytes were never initialized
		if (this->m_bytes == nullptr)
			return;

		this->m_bytes->Seek(0, SeekOrigin::Begin);
		if (this->m_bytes->Length > this->fgdbApiByteArray->allocatedLength)
			this->fgdbApiByteArray->Allocate((unsigned long)this->m_bytes->Length);
		
		unsigned char b;
		for (int i=0; i<this->m_bytes->Length; i++) {
			b = (unsigned char)this->m_bytes->ReadByte();
			memcpy(this->fgdbApiByteArray+i, &b, sizeof(unsigned char));
		}
	}
}