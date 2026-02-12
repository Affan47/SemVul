BYTE CjfifDecode::Buf(unsigned long nOffset,bool bClean=false)
{


	if (m_bBufFakeDHT) {
		return m_abMJPGDHTSeg[nOffset];
	} else {
		return m_pWBuf->Buf(nOffset,bClean);
	}
}
