read_metadata_block_data_cb_(FLAC__IOHandle handle, FLAC__IOCallback_Read read_cb, FLAC__IOCallback_Seek seek_cb, FLAC__StreamMetadata *block)
{
	switch(block->type) {
		case FLAC__METADATA_TYPE_STREAMINFO:
			return read_metadata_block_data_streaminfo_cb_(handle, read_cb, &block->data.stream_info);
		case FLAC__METADATA_TYPE_PADDING:
			return read_metadata_block_data_padding_cb_(handle, seek_cb, &block->data.padding, block->length);
		case FLAC__METADATA_TYPE_APPLICATION:
			return read_metadata_block_data_application_cb_(handle, read_cb, &block->data.application, block->length);
		case FLAC__METADATA_TYPE_SEEKTABLE:
			return read_metadata_block_data_seektable_cb_(handle, read_cb, &block->data.seek_table, block->length);
		case FLAC__METADATA_TYPE_VORBIS_COMMENT:
			return read_metadata_block_data_vorbis_comment_cb_(handle, read_cb, &block->data.vorbis_comment);
		case FLAC__METADATA_TYPE_CUESHEET:
			return read_metadata_block_data_cuesheet_cb_(handle, read_cb, &block->data.cue_sheet);
		case FLAC__METADATA_TYPE_PICTURE:
			return read_metadata_block_data_picture_cb_(handle, read_cb, &block->data.picture);
		default:
			return read_metadata_block_data_unknown_cb_(handle, read_cb, &block->data.unknown, block->length);
	}
}
