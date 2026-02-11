iNextByte(FILE *pFile)
{
	ULONG	ulReadOff;
	size_t	tReadLen;

	fail(pBlockCurrent == NULL);

	if (tByteNext >= sizeof(aucBlock) ||
	    ulBlockOffset + tByteNext >= pBlockCurrent->tInfo.ulLength) {
		if (ulBlockOffset + sizeof(aucBlock) <
					pBlockCurrent->tInfo.ulLength) {

			ulBlockOffset += sizeof(aucBlock);
		} else {

			pBlockCurrent = pBlockCurrent->pNext;
			ulBlockOffset = 0;
		}
		if (pBlockCurrent == NULL) {

			errno = EIO;
			return EOF;
		}
		tReadLen = (size_t)
				(pBlockCurrent->tInfo.ulLength - ulBlockOffset);
		if (tReadLen > sizeof(aucBlock)) {
			tReadLen = sizeof(aucBlock);
		}
		ulReadOff = pBlockCurrent->tInfo.ulFileOffset + ulBlockOffset;
		if (!bReadBytes(aucBlock, tReadLen, ulReadOff, pFile)) {
			errno = EIO;
			return EOF;
		}
		tByteNext = 0;
	}
	return (int)aucBlock[tByteNext++];
}
