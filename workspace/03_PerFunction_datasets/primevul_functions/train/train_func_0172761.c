unsigned CjfifDecode::ByteSwap4(unsigned nByte0,unsigned nByte1, unsigned nByte2, unsigned nByte3)
{
	unsigned nVal;

	if (m_nImgExifEndian == 0) {

		nVal = (nByte3<<24) + (nByte2<<16) + (nByte1<<8) + nByte0;
	} else {

		nVal = (nByte0<<24) + (nByte1<<16) + (nByte2<<8) + nByte3;
	}
	return nVal;
}
