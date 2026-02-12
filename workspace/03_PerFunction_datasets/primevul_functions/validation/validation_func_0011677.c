static OPJ_BOOL opj_j2k_init_info(opj_j2k_t *p_j2k,
                                  struct opj_stream_private *p_stream,
                                  struct opj_event_mgr * p_manager)
{
    opj_codestream_info_t * l_cstr_info = 00;


    assert(p_j2k != 00);
    assert(p_manager != 00);
    assert(p_stream != 00);
    (void)l_cstr_info;

    OPJ_UNUSED(p_stream);


    return opj_j2k_calculate_tp(p_j2k, &(p_j2k->m_cp),
                                &p_j2k->m_specific_param.m_encoder.m_total_tile_parts, p_j2k->m_private_image,
                                p_manager);
}
