write_metadata_block_data_unknown_cb_(FLAC__IOHandle handle, FLAC__IOCallback_Write write_cb, const FLAC__StreamMetadata_Unknown *block, unsigned block_length)
{
	if(write_cb(block->data, 1, block_length, handle) != block_length)
		return false;

	return true;
}
