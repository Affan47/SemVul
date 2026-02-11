bCheckBytes(FILE *pFile, const UCHAR *aucBytes, size_t tBytes)
{
	int	iIndex, iChar;

	fail(pFile == NULL || aucBytes == NULL || tBytes == 0);

	rewind(pFile);

	for (iIndex = 0; iIndex < (int)tBytes; iIndex++) {
		iChar = getc(pFile);
		if (iChar == EOF || iChar != (int)aucBytes[iIndex]) {
			NO_DBG_HEX(iChar);
			NO_DBG_HEX(aucBytes[iIndex]);
			return FALSE;
		}
	}
	return TRUE;
}
