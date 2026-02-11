charHandle(void *userdata, const XML_Char * data, int length) {
	static int bufsize = DATABUFSIZE;
	parsedata *pdata = (parsedata *) userdata;
	if (bufsize < length) {
		pdata->databuf = realloc(pdata->databuf, sizeof(char) * (length + 1));
		bufsize = length;
	}
	strncpy(pdata->databuf, data, length);
	pdata->bufptr = pdata->databuf;
	pdata->bufptr += length;
	*pdata->bufptr = '\0';
}
