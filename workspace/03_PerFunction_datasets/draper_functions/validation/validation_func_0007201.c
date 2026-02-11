git_inflate(z_streamp strm, int flush)
{
	int ret = inflate(strm, flush);
	const char *err;

	switch (ret) {

	case Z_MEM_ERROR:
		die("inflate: out of memory");


	case Z_NEED_DICT:
		err = "needs dictionary"; break;
	case Z_DATA_ERROR:
		err = "data stream error"; break;
	case Z_STREAM_ERROR:
		err = "stream consistency error"; break;
	default:
		err = "unknown error"; break;


	case Z_BUF_ERROR:
	case Z_OK:
	case Z_STREAM_END:
		return ret;
	}
	error("inflate: %s (%s)", err, strm->msg ? strm->msg : "no message");
	return ret;
}
