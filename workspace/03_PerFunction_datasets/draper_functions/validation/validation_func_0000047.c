flac_decoder_tell_callback(const FLAC__StreamDecoder *decoder, FLAC__uint64 *absolute_byte_offset, void *client_data)
{
	EncoderSession *e = (EncoderSession*)client_data;
	FLAC__off_t pos;
	(void)decoder;

	if((pos = ftello(e->fin)) < 0)
		return FLAC__STREAM_DECODER_TELL_STATUS_ERROR;
	else {
		*absolute_byte_offset = (FLAC__uint64)pos;
		return FLAC__STREAM_DECODER_TELL_STATUS_OK;
	}
}
