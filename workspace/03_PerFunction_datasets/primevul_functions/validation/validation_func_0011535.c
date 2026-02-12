static OPJ_BOOL opj_j2k_write_epc(opj_j2k_t *p_j2k,
                                  struct opj_stream_private *p_stream,
                                  struct opj_event_mgr * p_manager)
{
    opj_codestream_index_t * l_cstr_index = 00;


    assert(p_j2k != 00);
    assert(p_manager != 00);
    assert(p_stream != 00);

    OPJ_UNUSED(p_manager);

    l_cstr_index = p_j2k->cstr_index;
    if (l_cstr_index) {
        l_cstr_index->codestream_size = (OPJ_UINT64)opj_stream_tell(p_stream);


        l_cstr_index->codestream_size -= (OPJ_UINT64)l_cstr_index->main_head_start;

    }

#ifdef USE_JPWL

#if 0
    if (cp->epc_on) {


        jpwl_encode(p_j2k, p_stream, image);

    }
#endif
    assert(0 && "TODO");
#endif

    return OPJ_TRUE;
}
