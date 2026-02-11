iSaveDdsInternal()
{
	ILenum	DXTCFormat;
	ILuint	counter, numMipMaps, image, numFaces, i;
	ILubyte	*CurData = NULL;
	ILint	CubeTable[6] = { 0 };
	ILuint	CubeFlags;

	CubeFlags = GetCubemapInfo(iCurImage, CubeTable);

	image = ilGetInteger(IL_CUR_IMAGE);
	DXTCFormat = iGetInt(IL_DXTC_FORMAT);
	WriteHeader(iCurImage, DXTCFormat, CubeFlags);

	if (CubeFlags != 0)
		numFaces = ilGetInteger(IL_NUM_FACES);
	else
		numFaces = 0;

	numMipMaps = ilGetInteger(IL_NUM_MIPMAPS);

	for (i = 0; i <= numFaces; ++i) {
		for (counter = 0; counter <= numMipMaps; counter++) {
			ilBindImage(image);
			ilActiveImage(CubeTable[i]);
			ilActiveMipmap(counter);

			if (iCurImage->Origin != IL_ORIGIN_UPPER_LEFT) {
				CurData = iCurImage->Data;
				iCurImage->Data = iGetFlipped(iCurImage);
				if (iCurImage->Data == NULL) {
					iCurImage->Data = CurData;
					return IL_FALSE;
				}
			}

			if (!Compress(iCurImage, DXTCFormat))
				return IL_FALSE;

			if (iCurImage->Origin != IL_ORIGIN_UPPER_LEFT) {
				ifree(iCurImage->Data);
				iCurImage->Data = CurData;
			}
		}

	}

	return IL_TRUE;
}
