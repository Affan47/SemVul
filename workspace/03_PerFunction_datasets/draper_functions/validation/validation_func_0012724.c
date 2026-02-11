gf_jpeg_skip_input_data(j_decompress_ptr cinfo, long num_bytes)
{
	JPGCtx *jpx = (JPGCtx *) cinfo->src;
	if (num_bytes > (long) jpx->src.bytes_in_buffer) {
		jpx->skip = num_bytes - jpx->src.bytes_in_buffer;
		jpx->src.next_input_byte += jpx->src.bytes_in_buffer;
		jpx->src.bytes_in_buffer = 0;
	} else {
		jpx->src.bytes_in_buffer -= num_bytes;
		jpx->src.next_input_byte += num_bytes;
		jpx->skip = 0;
	}
}
