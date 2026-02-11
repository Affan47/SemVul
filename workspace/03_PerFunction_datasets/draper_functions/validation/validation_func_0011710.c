ilDetermineTypeF(ILHANDLE File)
{
	if (File == NULL)
		return IL_TYPE_UNKNOWN;

	#ifndef IL_NO_JPG
	if (ilIsValidJpegF(File))
		return IL_JPG;
	#endif

	#ifndef IL_NO_DDS
	if (ilIsValidDdsF(File))
		return IL_DDS;
	#endif

	#ifndef IL_NO_PNG
	if (ilIsValidPngF(File))
		return IL_PNG;
	#endif

	#ifndef IL_NO_BMP
	if (ilIsValidBmpF(File))
		return IL_BMP;
	#endif

	#ifndef IL_NO_EXR
	if (ilIsValidExrF(File))
		return IL_EXR;
	#endif

	#ifndef IL_NO_GIF
	if (ilIsValidGifF(File))
		return IL_GIF;
	#endif

	#ifndef IL_NO_HDR
	if (ilIsValidHdrF(File))
		return IL_HDR;
	#endif

	#ifndef IL_NO_ICNS
	if (ilIsValidIcnsF(File))
		return IL_ICNS;
	#endif

	#ifndef IL_NO_ILBM
	if (ilIsValidIlbmF(File))
		return IL_ILBM;
	#endif

	#ifndef IL_NO_IWI
	if (ilIsValidIwiF(File))
		return IL_IWI;
	#endif

	#ifndef IL_NO_JP2
	if (ilIsValidJp2F(File))
		return IL_JP2;
	#endif

	#ifndef IL_NO_LIF
	if (ilIsValidLifF(File))
		return IL_LIF;
	#endif

	#ifndef IL_NO_MDL
	if (ilIsValidMdlF(File))
		return IL_MDL;
	#endif

	#ifndef IL_NO_MP3
	if (ilIsValidMp3F(File))
		return IL_MP3;
	#endif

	#ifndef IL_NO_PCX
	if (ilIsValidPcxF(File))
		return IL_PCX;
	#endif

	#ifndef IL_NO_PIC
	if (ilIsValidPicF(File))
		return IL_PIC;
	#endif

	#ifndef IL_NO_PNM
	if (ilIsValidPnmF(File))
		return IL_PNM;
	#endif

	#ifndef IL_NO_PSD
	if (ilIsValidPsdF(File))
		return IL_PSD;
	#endif

	#ifndef IL_NO_PSP
	if (ilIsValidPspF(File))
		return IL_PSP;
	#endif

	#ifndef IL_NO_SGI
	if (ilIsValidSgiF(File))
		return IL_SGI;
	#endif

	#ifndef IL_NO_SUN
	if (ilIsValidSunF(File))
		return IL_SUN;
	#endif

	#ifndef IL_NO_TIF
	if (ilIsValidTiffF(File))
		return IL_TIF;
	#endif

	#ifndef IL_NO_TPL
	if (ilIsValidTplF(File))
		return IL_TPL;
	#endif

	#ifndef IL_NO_VTF
	if (ilIsValidVtfF(File))
		return IL_VTF;
	#endif

	#ifndef IL_NO_XPM
	if (ilIsValidXpmF(File))
		return IL_XPM;
	#endif


	#ifndef IL_NO_TGA
	if (ilIsValidTgaF(File))
		return IL_TGA;
	#endif

	return IL_TYPE_UNKNOWN;
}
