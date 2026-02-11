x264_cqm_delete( x264_t *h )
{
    CQM_DELETE( 4, 4 );
    CQM_DELETE( 8, CHROMA444 ? 4 : 2 );
    x264_free( h->nr_offset_emergency );
}
