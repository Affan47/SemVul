opj_j2k_write_tile (opj_j2k_t * p_j2k,
                                                 OPJ_UINT32 p_tile_index,
                                                 OPJ_BYTE * p_data,
                                                 OPJ_UINT32 p_data_size,
                                                 opj_stream_private_t *p_stream,
                                                 opj_event_mgr_t * p_manager )
{
        if (! opj_j2k_pre_write_tile(p_j2k,p_tile_index,p_stream,p_manager)) {
                opj_event_msg(p_manager, EVT_ERROR, "Error while opj_j2k_pre_write_tile with tile index = %d\n", p_tile_index);
                return OPJ_FALSE;
        }
        else {
                if (! opj_j2k_post_write_tile(p_j2k,p_data,p_data_size,p_stream,p_manager)) {
                        opj_event_msg(p_manager, EVT_ERROR, "Error while opj_j2k_post_write_tile with tile index = %d\n", p_tile_index);
                        return OPJ_FALSE;
                }
        }

        return OPJ_TRUE;
}
