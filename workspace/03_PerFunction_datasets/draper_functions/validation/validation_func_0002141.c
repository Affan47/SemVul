useFontConfig(int flag)
{
#ifdef HAVE_LIBFONTCONFIG
	if (fontConfigFlag) {
		return (!(flag & gdFTEX_FONTPATHNAME));
	} else
#endif
	{
		return flag & gdFTEX_FONTCONFIG;

	}
	return flag & gdFTEX_FONTCONFIG;
}
