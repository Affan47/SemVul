OPJ_BOOL opj_j2k_decode_tile (  opj_j2k_t * p_j2k,
                                                        OPJ_UINT32 p_tile_index,
                                                        OPJ_BYTE * p_data,
                                                        OPJ_UINT32 p_data_size,
                                                        opj_stream_private_t *p_stream,
                                                        opj_event_mgr_t * p_manager )
{
        OPJ_UINT32 l_current_marker;
        OPJ_BYTE l_data [2];
        opj_tcp_t * l_tcp;


        assert(p_stream != 00);
        assert(p_j2k != 00);
        assert(p_manager != 00);

        if ( !(p_j2k->m_specific_param.m_decoder.m_state & 0x0080)
                || (p_tile_index != p_j2k->m_current_tile_number) ) {
                return OPJ_FALSE;
        }

        l_tcp = &(p_j2k->m_cp.tcps[p_tile_index]);
        if (! l_tcp->m_data) {
                opj_j2k_tcp_destroy(l_tcp);
                return OPJ_FALSE;
        }

        if (! opj_tcd_decode_tile(      p_j2k->m_tcd,
                                                                l_tcp->m_data,
                                                                l_tcp->m_data_size,
                                                                p_tile_index,
                                                                p_j2k->cstr_index) ) {
                opj_j2k_tcp_destroy(l_tcp);
                p_j2k->m_specific_param.m_decoder.m_state |= 0x8000;
                opj_event_msg(p_manager, EVT_ERROR, "Failed to decode.\n");
                return OPJ_FALSE;
        }

        if (! opj_tcd_update_tile_data(p_j2k->m_tcd,p_data,p_data_size)) {
                return OPJ_FALSE;
        }


        opj_j2k_tcp_data_destroy(l_tcp);

        p_j2k->m_specific_param.m_decoder.m_can_decode = 0;
        p_j2k->m_specific_param.m_decoder.m_state &= (~ (0x0080u));

        if(opj_stream_get_number_byte_left(p_stream) == 0
            && p_j2k->m_specific_param.m_decoder.m_state == J2K_STATE_NEOC){
            return OPJ_TRUE;
        }

        if (p_j2k->m_specific_param.m_decoder.m_state != 0x0100){
                if (opj_stream_read_data(p_stream,l_data,2,p_manager) != 2) {
                        opj_event_msg(p_manager, EVT_ERROR, "Stream too short\n");
                        return OPJ_FALSE;
                }

                opj_read_bytes(l_data,&l_current_marker,2);

                if (l_current_marker == J2K_MS_EOC) {
                        p_j2k->m_current_tile_number = 0;
                        p_j2k->m_specific_param.m_decoder.m_state =  0x0100;
                }
                else if (l_current_marker != J2K_MS_SOT)
                {
                        if(opj_stream_get_number_byte_left(p_stream) == 0) {
                            p_j2k->m_specific_param.m_decoder.m_state = J2K_STATE_NEOC;
                            opj_event_msg(p_manager, EVT_WARNING, "Stream does not end with EOC\n");
                            return OPJ_TRUE;
                        }
                        opj_event_msg(p_manager, EVT_ERROR, "Stream too short, expected SOT\n");
                        return OPJ_FALSE;
                }
        }

        return OPJ_TRUE;
}
