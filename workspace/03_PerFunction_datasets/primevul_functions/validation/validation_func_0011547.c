static OPJ_BOOL opj_j2k_write_eoc(opj_j2k_t *p_j2k,
                                  opj_stream_private_t *p_stream,
                                  opj_event_mgr_t * p_manager
                                 )
{

    assert(p_j2k != 00);
    assert(p_manager != 00);
    assert(p_stream != 00);

    opj_write_bytes(p_j2k->m_specific_param.m_encoder.m_header_tile_data,
                    J2K_MS_EOC, 2);


#ifdef USE_JPWL


#endif

    if (opj_stream_write_data(p_stream,
                              p_j2k->m_specific_param.m_encoder.m_header_tile_data, 2, p_manager) != 2) {
        return OPJ_FALSE;
    }

    if (! opj_stream_flush(p_stream, p_manager)) {
        return OPJ_FALSE;
    }

    return OPJ_TRUE;
}
