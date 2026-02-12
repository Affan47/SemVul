static OPJ_BOOL opj_j2k_read_plm(opj_j2k_t *p_j2k,
                                 OPJ_BYTE * p_header_data,
                                 OPJ_UINT32 p_header_size,
                                 opj_event_mgr_t * p_manager
                                )
{

    assert(p_header_data != 00);
    assert(p_j2k != 00);
    assert(p_manager != 00);

    OPJ_UNUSED(p_j2k);
    OPJ_UNUSED(p_header_data);

    if (p_header_size < 1) {
        opj_event_msg(p_manager, EVT_ERROR, "Error reading PLM marker\n");
        return OPJ_FALSE;
    }


    return OPJ_TRUE;
}
