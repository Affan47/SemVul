std_fill_input_buffer(j_decompress_ptr cinfo)
{
	JPEGState* sp = (JPEGState* ) cinfo;
	static const JOCTET dummy_EOI[2] = { 0xFF, JPEG_EOI };

#ifdef IPPJ_HUFF


        if( sp->src.bytes_in_buffer > 0 ) {
            return (TRUE);
        }
#endif


	WARNMS(cinfo, JWRN_JPEG_EOF);

	sp->src.next_input_byte = dummy_EOI;
	sp->src.bytes_in_buffer = 2;
	return (TRUE);
}
