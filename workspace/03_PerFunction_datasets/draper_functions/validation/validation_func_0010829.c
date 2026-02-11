file_seek_callback_(const FLAC__StreamEncoder *encoder, FLAC__uint64 absolute_byte_offset, void *client_data)
{
	(void)client_data;

	if(fseeko(encoder->private_->file, (FLAC__off_t)absolute_byte_offset, SEEK_SET) < 0)
		return FLAC__STREAM_ENCODER_SEEK_STATUS_ERROR;
	else
		return FLAC__STREAM_ENCODER_SEEK_STATUS_OK;
}
