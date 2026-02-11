bTranslateDIB(diagram_type *pDiag, FILE *pInFile,
		ULONG ulFileOffset, const imagedata_type *pImg)
{
#if defined(DEBUG)
	fail(pImg->tPosition > pImg->tLength);
	vCopy2File(pInFile, ulFileOffset, pImg->tLength - pImg->tPosition);
#endif


	if (!bSetDataOffset(pInFile, ulFileOffset)) {
		return FALSE;
	}

	vImagePrologue(pDiag, pImg);
	vDecodeDIB(pInFile, pDiag->pOutFile, pImg);
	vImageEpilogue(pDiag);

	return TRUE;
}
