u_Open(char *path, STREAM_COMPRESS *stream)
{
	char mode[3]={'r','b',0};

	stream->desc = &ZStream;
	stream->mode = MODE_READ;
	stream->handle = gzopen(path, mode);

	if (stream->handle) return;

	stream->desc=NULL;
	if ( errno == Z_MEM_ERROR )
	{
		GB.Error("Not enough memory to manage selected file");
		return;
	}

	GB.Error("Unable to open selected file");
}
