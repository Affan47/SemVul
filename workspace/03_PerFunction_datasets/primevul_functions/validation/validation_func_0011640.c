static OPJ_BOOL opj_j2k_encoding_validation(opj_j2k_t * p_j2k,
        opj_stream_private_t *p_stream,
        opj_event_mgr_t * p_manager)
{
    OPJ_BOOL l_is_valid = OPJ_TRUE;


    assert(p_j2k != 00);
    assert(p_stream != 00);
    assert(p_manager != 00);

    OPJ_UNUSED(p_stream);


    l_is_valid &= (p_j2k->m_specific_param.m_decoder.m_state == J2K_STATE_NONE);


    l_is_valid &= (p_j2k->m_procedure_list != 00);

    l_is_valid &= (p_j2k->m_validation_list != 00);


    if ((p_j2k->m_cp.tcps->tccps->numresolutions <= 0) ||
            (p_j2k->m_cp.tcps->tccps->numresolutions > 32)) {
        opj_event_msg(p_manager, EVT_ERROR,
                      "Number of resolutions is too high in comparison to the size of tiles\n");
        return OPJ_FALSE;
    }

    if ((p_j2k->m_cp.tdx) < (OPJ_UINT32)(1 <<
                                         (p_j2k->m_cp.tcps->tccps->numresolutions - 1U))) {
        opj_event_msg(p_manager, EVT_ERROR,
                      "Number of resolutions is too high in comparison to the size of tiles\n");
        return OPJ_FALSE;
    }

    if ((p_j2k->m_cp.tdy) < (OPJ_UINT32)(1 <<
                                         (p_j2k->m_cp.tcps->tccps->numresolutions - 1U))) {
        opj_event_msg(p_manager, EVT_ERROR,
                      "Number of resolutions is too high in comparison to the size of tiles\n");
        return OPJ_FALSE;
    }


    return l_is_valid;
}
