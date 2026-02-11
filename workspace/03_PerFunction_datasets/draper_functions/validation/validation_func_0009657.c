asf_get_stream_count(asf_file_t *file)
{
	uint8_t ret = 0;
	int i;

	for (i = 0; i < ASF_MAX_STREAMS; i++) {
		if (file->streams[i].type != ASF_STREAM_TYPE_NONE)
			ret = i;
	}

	return ret;
}
