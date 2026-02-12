TIFFjpeg_error_exit(j_common_ptr cinfo)
{
	JPEGState *sp = (JPEGState *) cinfo;
	char buffer[JMSG_LENGTH_MAX];

	(*cinfo->err->format_message) (cinfo, buffer);
	TIFFErrorExt(sp->tif->tif_clientdata, "JPEGLib", "%s", buffer);
	jpeg_abort(cinfo);
	LONGJMP(sp->exit_jmpbuf, 1);
}
