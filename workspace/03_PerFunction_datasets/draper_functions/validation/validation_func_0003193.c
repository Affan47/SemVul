ReadAndDecrypt(FILE * fp, void *lp, int nLen,
			     const int *nEncStream, int &nEncIndex)
{
	int i;
	fread(lp, nLen, 1, fp);
	for (i = 0; i < nLen; i++) {
		((uint8_t *) lp)[i] -= nEncStream[nEncIndex];
		nEncIndex = (nEncIndex + 1) % 32;
	}
}
