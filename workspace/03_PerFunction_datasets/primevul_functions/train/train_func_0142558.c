OPJ_BOOL opj_j2k_read_tile_header(opj_j2k_t * p_j2k,
                                  OPJ_UINT32 * p_tile_index,
                                  OPJ_UINT32 * p_data_size,
                                  OPJ_INT32 * p_tile_x0, OPJ_INT32 * p_tile_y0,
                                  OPJ_INT32 * p_tile_x1, OPJ_INT32 * p_tile_y1,
                                  OPJ_UINT32 * p_nb_comps,
                                  OPJ_BOOL * p_go_on,
                                  opj_stream_private_t *p_stream,
                                  opj_event_mgr_t * p_manager)
{
    OPJ_UINT32 l_current_marker = J2K_MS_SOT;
    OPJ_UINT32 l_marker_size;
    const opj_dec_memory_marker_handler_t * l_marker_handler = 00;
    opj_tcp_t * l_tcp = NULL;


    assert(p_stream != 00);
    assert(p_j2k != 00);
    assert(p_manager != 00);


    if (p_j2k->m_specific_param.m_decoder.m_state == J2K_STATE_EOC) {
        l_current_marker = J2K_MS_EOC;
    }

    else if (p_j2k->m_specific_param.m_decoder.m_state != J2K_STATE_TPHSOT) {
        return OPJ_FALSE;
    }


    while ((!p_j2k->m_specific_param.m_decoder.m_can_decode) &&
            (l_current_marker != J2K_MS_EOC)) {


        while (l_current_marker != J2K_MS_SOD) {

            if (opj_stream_get_number_byte_left(p_stream) == 0) {
                p_j2k->m_specific_param.m_decoder.m_state = J2K_STATE_NEOC;
                break;
            }


            if (opj_stream_read_data(p_stream,
                                     p_j2k->m_specific_param.m_decoder.m_header_data, 2, p_manager) != 2) {
                opj_event_msg(p_manager, EVT_ERROR, "Stream too short\n");
                return OPJ_FALSE;
            }


            opj_read_bytes(p_j2k->m_specific_param.m_decoder.m_header_data, &l_marker_size,
                           2);


            if (l_marker_size < 2) {
                opj_event_msg(p_manager, EVT_ERROR, "Inconsistent marker size\n");
                return OPJ_FALSE;
            }


            if (l_current_marker == 0x8080 &&
                    opj_stream_get_number_byte_left(p_stream) == 0) {
                p_j2k->m_specific_param.m_decoder.m_state = J2K_STATE_NEOC;
                break;
            }


            if (p_j2k->m_specific_param.m_decoder.m_state & J2K_STATE_TPH) {
                p_j2k->m_specific_param.m_decoder.m_sot_length -= (l_marker_size + 2);
            }
            l_marker_size -= 2;


            l_marker_handler = opj_j2k_get_marker_handler(l_current_marker);


            if (!(p_j2k->m_specific_param.m_decoder.m_state & l_marker_handler->states)) {
                opj_event_msg(p_manager, EVT_ERROR,
                              "Marker is not compliant with its position\n");
                return OPJ_FALSE;
            }


            if (l_marker_size > p_j2k->m_specific_param.m_decoder.m_header_data_size) {
                OPJ_BYTE *new_header_data = NULL;


                if ((OPJ_OFF_T)l_marker_size >  opj_stream_get_number_byte_left(p_stream)) {
                    opj_event_msg(p_manager, EVT_ERROR,
                                  "Marker size inconsistent with stream length\n");
                    return OPJ_FALSE;
                }
                new_header_data = (OPJ_BYTE *) opj_realloc(
                                      p_j2k->m_specific_param.m_decoder.m_header_data, l_marker_size);
                if (! new_header_data) {
                    opj_free(p_j2k->m_specific_param.m_decoder.m_header_data);
                    p_j2k->m_specific_param.m_decoder.m_header_data = NULL;
                    p_j2k->m_specific_param.m_decoder.m_header_data_size = 0;
                    opj_event_msg(p_manager, EVT_ERROR, "Not enough memory to read header\n");
                    return OPJ_FALSE;
                }
                p_j2k->m_specific_param.m_decoder.m_header_data = new_header_data;
                p_j2k->m_specific_param.m_decoder.m_header_data_size = l_marker_size;
            }


            if (opj_stream_read_data(p_stream,
                                     p_j2k->m_specific_param.m_decoder.m_header_data, l_marker_size,
                                     p_manager) != l_marker_size) {
                opj_event_msg(p_manager, EVT_ERROR, "Stream too short\n");
                return OPJ_FALSE;
            }

            if (!l_marker_handler->handler) {

                opj_event_msg(p_manager, EVT_ERROR, "Not sure how that happened.\n");
                return OPJ_FALSE;
            }

            if (!(*(l_marker_handler->handler))(p_j2k,
                                                p_j2k->m_specific_param.m_decoder.m_header_data, l_marker_size, p_manager)) {
                opj_event_msg(p_manager, EVT_ERROR,
                              "Fail to read the current marker segment (%#x)\n", l_current_marker);
                return OPJ_FALSE;
            }


            if (OPJ_FALSE == opj_j2k_add_tlmarker(p_j2k->m_current_tile_number,
                                                  p_j2k->cstr_index,
                                                  l_marker_handler->id,
                                                  (OPJ_UINT32) opj_stream_tell(p_stream) - l_marker_size - 4,
                                                  l_marker_size + 4)) {
                opj_event_msg(p_manager, EVT_ERROR, "Not enough memory to add tl marker\n");
                return OPJ_FALSE;
            }


            if (l_marker_handler->id == J2K_MS_SOT) {
                OPJ_UINT32 sot_pos = (OPJ_UINT32) opj_stream_tell(p_stream) - l_marker_size - 4
                                     ;
                if (sot_pos > p_j2k->m_specific_param.m_decoder.m_last_sot_read_pos) {
                    p_j2k->m_specific_param.m_decoder.m_last_sot_read_pos = sot_pos;
                }
            }

            if (p_j2k->m_specific_param.m_decoder.m_skip_data) {

                if (opj_stream_skip(p_stream, p_j2k->m_specific_param.m_decoder.m_sot_length,
                                    p_manager) != p_j2k->m_specific_param.m_decoder.m_sot_length) {
                    opj_event_msg(p_manager, EVT_ERROR, "Stream too short\n");
                    return OPJ_FALSE;
                }
                l_current_marker = J2K_MS_SOD;
            } else {

                if (opj_stream_read_data(p_stream,
                                         p_j2k->m_specific_param.m_decoder.m_header_data, 2, p_manager) != 2) {
                    opj_event_msg(p_manager, EVT_ERROR, "Stream too short\n");
                    return OPJ_FALSE;
                }

                opj_read_bytes(p_j2k->m_specific_param.m_decoder.m_header_data,
                               &l_current_marker, 2);
            }
        }
        if (opj_stream_get_number_byte_left(p_stream) == 0
                && p_j2k->m_specific_param.m_decoder.m_state == J2K_STATE_NEOC) {
            break;
        }


        if (! p_j2k->m_specific_param.m_decoder.m_skip_data) {

            if (! opj_j2k_read_sod(p_j2k, p_stream, p_manager)) {
                return OPJ_FALSE;
            }
            if (p_j2k->m_specific_param.m_decoder.m_can_decode &&
                    !p_j2k->m_specific_param.m_decoder.m_nb_tile_parts_correction_checked) {

                OPJ_BOOL l_correction_needed;

                p_j2k->m_specific_param.m_decoder.m_nb_tile_parts_correction_checked = 1;
                if (!opj_j2k_need_nb_tile_parts_correction(p_stream,
                        p_j2k->m_current_tile_number, &l_correction_needed, p_manager)) {
                    opj_event_msg(p_manager, EVT_ERROR,
                                  "opj_j2k_apply_nb_tile_parts_correction error\n");
                    return OPJ_FALSE;
                }
                if (l_correction_needed) {
                    OPJ_UINT32 l_nb_tiles = p_j2k->m_cp.tw * p_j2k->m_cp.th;
                    OPJ_UINT32 l_tile_no;

                    p_j2k->m_specific_param.m_decoder.m_can_decode = 0;
                    p_j2k->m_specific_param.m_decoder.m_nb_tile_parts_correction = 1;

                    for (l_tile_no = 0U; l_tile_no < l_nb_tiles; ++l_tile_no) {
                        if (p_j2k->m_cp.tcps[l_tile_no].m_nb_tile_parts != 0U) {
                            p_j2k->m_cp.tcps[l_tile_no].m_nb_tile_parts += 1;
                        }
                    }
                    opj_event_msg(p_manager, EVT_WARNING,
                                  "Non conformant codestream TPsot==TNsot.\n");
                }
            }
            if (! p_j2k->m_specific_param.m_decoder.m_can_decode) {

                if (opj_stream_read_data(p_stream,
                                         p_j2k->m_specific_param.m_decoder.m_header_data, 2, p_manager) != 2) {
                    opj_event_msg(p_manager, EVT_ERROR, "Stream too short\n");
                    return OPJ_FALSE;
                }


                opj_read_bytes(p_j2k->m_specific_param.m_decoder.m_header_data,
                               &l_current_marker, 2);
            }
        } else {

            p_j2k->m_specific_param.m_decoder.m_skip_data = 0;
            p_j2k->m_specific_param.m_decoder.m_can_decode = 0;
            p_j2k->m_specific_param.m_decoder.m_state = J2K_STATE_TPHSOT;


            if (opj_stream_read_data(p_stream,
                                     p_j2k->m_specific_param.m_decoder.m_header_data, 2, p_manager) != 2) {
                opj_event_msg(p_manager, EVT_ERROR, "Stream too short\n");
                return OPJ_FALSE;
            }


            opj_read_bytes(p_j2k->m_specific_param.m_decoder.m_header_data,
                           &l_current_marker, 2);
        }
    }


    if (l_current_marker == J2K_MS_EOC) {
        p_j2k->m_specific_param.m_decoder.m_state = J2K_STATE_EOC;
    }


    if (! p_j2k->m_specific_param.m_decoder.m_can_decode) {
        OPJ_UINT32 l_nb_tiles = p_j2k->m_cp.th * p_j2k->m_cp.tw;
        l_tcp = p_j2k->m_cp.tcps + p_j2k->m_current_tile_number;

        while ((p_j2k->m_current_tile_number < l_nb_tiles) && (l_tcp->m_data == 00)) {
            ++p_j2k->m_current_tile_number;
            ++l_tcp;
        }

        if (p_j2k->m_current_tile_number == l_nb_tiles) {
            *p_go_on = OPJ_FALSE;
            return OPJ_TRUE;
        }
    }

    if (! opj_j2k_merge_ppt(p_j2k->m_cp.tcps + p_j2k->m_current_tile_number,
                            p_manager)) {
        opj_event_msg(p_manager, EVT_ERROR, "Failed to merge PPT data\n");
        return OPJ_FALSE;
    }

    if (! opj_tcd_init_decode_tile(p_j2k->m_tcd, p_j2k->m_current_tile_number,
                                   p_manager)) {
        opj_event_msg(p_manager, EVT_ERROR, "Cannot decode tile, memory error\n");
        return OPJ_FALSE;
    }

    opj_event_msg(p_manager, EVT_INFO, "Header of tile %d / %d has been read.\n",
                  p_j2k->m_current_tile_number + 1, (p_j2k->m_cp.th * p_j2k->m_cp.tw));

    *p_tile_index = p_j2k->m_current_tile_number;
    *p_go_on = OPJ_TRUE;
    *p_data_size = opj_tcd_get_decoded_tile_size(p_j2k->m_tcd);
    if (*p_data_size == UINT_MAX) {
        return OPJ_FALSE;
    }
    *p_tile_x0 = p_j2k->m_tcd->tcd_image->tiles->x0;
    *p_tile_y0 = p_j2k->m_tcd->tcd_image->tiles->y0;
    *p_tile_x1 = p_j2k->m_tcd->tcd_image->tiles->x1;
    *p_tile_y1 = p_j2k->m_tcd->tcd_image->tiles->y1;
    *p_nb_comps = p_j2k->m_tcd->tcd_image->tiles->numcomps;

    p_j2k->m_specific_param.m_decoder.m_state |= J2K_STATE_DATA;

    return OPJ_TRUE;
}
