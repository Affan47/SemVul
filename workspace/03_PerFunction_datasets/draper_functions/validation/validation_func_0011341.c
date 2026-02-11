get_qt_dynamic(unsigned char *pIn, struct comp_info *cinfo)
{
	int rawLen = cinfo->rawLen;


	if (rawLen < 72)
		return -1;

	cinfo->qt = pIn + rawLen - 64;

	return 0;
}
