unsigned CjfifDecode::ByteSwap2(unsigned nByte0,unsigned nByte1)
{
	unsigned nVal;
	if (m_nImgExifEndian == 0) {

		nVal = (nByte1<<8) + nByte0;
	} else {

		nVal = (nByte0<<8) + nByte1;
	}
	return nVal;
}
