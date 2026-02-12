tables_term_destination(j_compress_ptr cinfo)
{
	JPEGState* sp = (JPEGState*) cinfo;


	sp->jpegtables_length -= (uint32) sp->dest.free_in_buffer;
}
