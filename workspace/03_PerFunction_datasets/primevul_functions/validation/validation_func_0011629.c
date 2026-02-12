static OPJ_BOOL opj_j2k_read_sot(opj_j2k_t *p_j2k,
                                 OPJ_BYTE * p_header_data,
                                 OPJ_UINT32 p_header_size,
                                 opj_event_mgr_t * p_manager)
{
    opj_cp_t *l_cp = 00;
    opj_tcp_t *l_tcp = 00;
    OPJ_UINT32 l_tot_len, l_num_parts = 0;
    OPJ_UINT32 l_current_part;
    OPJ_UINT32 l_tile_x, l_tile_y;


    assert(p_j2k != 00);
    assert(p_manager != 00);

    if (! opj_j2k_get_sot_values(p_header_data, p_header_size,
                                 &(p_j2k->m_current_tile_number), &l_tot_len, &l_current_part, &l_num_parts,
                                 p_manager)) {
        opj_event_msg(p_manager, EVT_ERROR, "Error reading SOT marker\n");
        return OPJ_FALSE;
    }
#ifdef DEBUG_VERBOSE
    fprintf(stderr, "SOT %d %d %d %d\n",
            p_j2k->m_current_tile_number, l_tot_len, l_current_part, l_num_parts);
#endif

    l_cp = &(p_j2k->m_cp);


    if (p_j2k->m_current_tile_number >= l_cp->tw * l_cp->th) {
        opj_event_msg(p_manager, EVT_ERROR, "Invalid tile number %d\n",
                      p_j2k->m_current_tile_number);
        return OPJ_FALSE;
    }

    l_tcp = &l_cp->tcps[p_j2k->m_current_tile_number];
    l_tile_x = p_j2k->m_current_tile_number % l_cp->tw;
    l_tile_y = p_j2k->m_current_tile_number / l_cp->tw;

    if (p_j2k->m_specific_param.m_decoder.m_tile_ind_to_dec < 0 ||
            p_j2k->m_current_tile_number == (OPJ_UINT32)
            p_j2k->m_specific_param.m_decoder.m_tile_ind_to_dec) {


        if (l_tcp->m_current_tile_part_number + 1 != (OPJ_INT32)l_current_part) {
            opj_event_msg(p_manager, EVT_ERROR,
                          "Invalid tile part index for tile number %d. "
                          "Got %d, expected %d\n",
                          p_j2k->m_current_tile_number,
                          l_current_part,
                          l_tcp->m_current_tile_part_number + 1);
            return OPJ_FALSE;
        }
    }

    l_tcp->m_current_tile_part_number = (OPJ_INT32) l_current_part;

#ifdef USE_JPWL
    if (l_cp->correct) {

        OPJ_UINT32 tileno = p_j2k->m_current_tile_number;
        static OPJ_UINT32 backup_tileno = 0;


        if (tileno > (l_cp->tw * l_cp->th)) {
            opj_event_msg(p_manager, EVT_ERROR,
                          "JPWL: bad tile number (%d out of a maximum of %d)\n",
                          tileno, (l_cp->tw * l_cp->th));
            if (!JPWL_ASSUME) {
                opj_event_msg(p_manager, EVT_ERROR, "JPWL: giving up\n");
                return OPJ_FALSE;
            }

            tileno = backup_tileno;
            opj_event_msg(p_manager, EVT_WARNING, "- trying to adjust this\n"
                          "- setting tile number to %d\n",
                          tileno);
        }


        backup_tileno++;
    };
#endif


    if ((l_tot_len != 0) && (l_tot_len < 14)) {
        if (l_tot_len ==
                12) {
            opj_event_msg(p_manager, EVT_WARNING, "Empty SOT marker detected: Psot=%d.\n",
                          l_tot_len);
        } else {
            opj_event_msg(p_manager, EVT_ERROR,
                          "Psot value is not correct regards to the JPEG2000 norm: %d.\n", l_tot_len);
            return OPJ_FALSE;
        }
    }

#ifdef USE_JPWL
    if (l_cp->correct) {


        if ( (l_tot_len >
                                    p_header_size)) {
            opj_event_msg(p_manager, EVT_ERROR,
                          "JPWL: bad tile byte size (%d bytes against %d bytes left)\n",
                          l_tot_len,
                          p_header_size);
            if (!JPWL_ASSUME) {
                opj_event_msg(p_manager, EVT_ERROR, "JPWL: giving up\n");
                return OPJ_FALSE;
            }

            l_tot_len = 0;
            opj_event_msg(p_manager, EVT_WARNING, "- trying to adjust this\n"
                          "- setting Psot to %d => assuming it is the last tile\n",
                          l_tot_len);
        }
    };
#endif


    if (!l_tot_len) {
        opj_event_msg(p_manager, EVT_INFO,
                      "Psot value of the current tile-part is equal to zero, "
                      "we assuming it is the last tile-part of the codestream.\n");
        p_j2k->m_specific_param.m_decoder.m_last_tile_part = 1;
    }

    if (l_tcp->m_nb_tile_parts != 0 && l_current_part >= l_tcp->m_nb_tile_parts) {

        opj_event_msg(p_manager, EVT_ERROR,
                      "In SOT marker, TPSot (%d) is not valid regards to the previous "
                      "number of tile-part (%d), giving up\n", l_current_part,
                      l_tcp->m_nb_tile_parts);
        p_j2k->m_specific_param.m_decoder.m_last_tile_part = 1;
        return OPJ_FALSE;
    }

    if (l_num_parts !=
            0) {
        l_num_parts += p_j2k->m_specific_param.m_decoder.m_nb_tile_parts_correction;


        if (l_tcp->m_nb_tile_parts) {
            if (l_current_part >= l_tcp->m_nb_tile_parts) {
                opj_event_msg(p_manager, EVT_ERROR,
                              "In SOT marker, TPSot (%d) is not valid regards to the current "
                              "number of tile-part (%d), giving up\n", l_current_part,
                              l_tcp->m_nb_tile_parts);
                p_j2k->m_specific_param.m_decoder.m_last_tile_part = 1;
                return OPJ_FALSE;
            }
        }
        if (l_current_part >= l_num_parts) {

            opj_event_msg(p_manager, EVT_ERROR,
                          "In SOT marker, TPSot (%d) is not valid regards to the current "
                          "number of tile-part (header) (%d), giving up\n", l_current_part, l_num_parts);
            p_j2k->m_specific_param.m_decoder.m_last_tile_part = 1;
            return OPJ_FALSE;
        }
        l_tcp->m_nb_tile_parts = l_num_parts;
    }


    if (l_tcp->m_nb_tile_parts) {
        if (l_tcp->m_nb_tile_parts == (l_current_part + 1)) {
            p_j2k->m_specific_param.m_decoder.m_can_decode =
                1;
        }
    }

    if (!p_j2k->m_specific_param.m_decoder.m_last_tile_part) {

        p_j2k->m_specific_param.m_decoder.m_sot_length = l_tot_len -
                12;
    } else {

        p_j2k->m_specific_param.m_decoder.m_sot_length = 0;
    }

    p_j2k->m_specific_param.m_decoder.m_state = J2K_STATE_TPH;


    if (p_j2k->m_specific_param.m_decoder.m_tile_ind_to_dec == -1) {
        p_j2k->m_specific_param.m_decoder.m_skip_data =
            (l_tile_x < p_j2k->m_specific_param.m_decoder.m_start_tile_x)
            || (l_tile_x >= p_j2k->m_specific_param.m_decoder.m_end_tile_x)
            || (l_tile_y < p_j2k->m_specific_param.m_decoder.m_start_tile_y)
            || (l_tile_y >= p_j2k->m_specific_param.m_decoder.m_end_tile_y);
    } else {
        assert(p_j2k->m_specific_param.m_decoder.m_tile_ind_to_dec >= 0);
        p_j2k->m_specific_param.m_decoder.m_skip_data =
            (p_j2k->m_current_tile_number != (OPJ_UINT32)
             p_j2k->m_specific_param.m_decoder.m_tile_ind_to_dec);
    }


    if (p_j2k->cstr_index) {
        assert(p_j2k->cstr_index->tile_index != 00);
        p_j2k->cstr_index->tile_index[p_j2k->m_current_tile_number].tileno =
            p_j2k->m_current_tile_number;
        p_j2k->cstr_index->tile_index[p_j2k->m_current_tile_number].current_tpsno =
            l_current_part;

        if (l_num_parts != 0) {
            p_j2k->cstr_index->tile_index[p_j2k->m_current_tile_number].nb_tps =
                l_num_parts;
            p_j2k->cstr_index->tile_index[p_j2k->m_current_tile_number].current_nb_tps =
                l_num_parts;

            if (!p_j2k->cstr_index->tile_index[p_j2k->m_current_tile_number].tp_index) {
                p_j2k->cstr_index->tile_index[p_j2k->m_current_tile_number].tp_index =
                    (opj_tp_index_t*)opj_calloc(l_num_parts, sizeof(opj_tp_index_t));
                if (!p_j2k->cstr_index->tile_index[p_j2k->m_current_tile_number].tp_index) {
                    opj_event_msg(p_manager, EVT_ERROR,
                                  "Not enough memory to read SOT marker. Tile index allocation failed\n");
                    return OPJ_FALSE;
                }
            } else {
                opj_tp_index_t *new_tp_index = (opj_tp_index_t *) opj_realloc(
                                                   p_j2k->cstr_index->tile_index[p_j2k->m_current_tile_number].tp_index,
                                                   l_num_parts * sizeof(opj_tp_index_t));
                if (! new_tp_index) {
                    opj_free(p_j2k->cstr_index->tile_index[p_j2k->m_current_tile_number].tp_index);
                    p_j2k->cstr_index->tile_index[p_j2k->m_current_tile_number].tp_index = NULL;
                    opj_event_msg(p_manager, EVT_ERROR,
                                  "Not enough memory to read SOT marker. Tile index allocation failed\n");
                    return OPJ_FALSE;
                }
                p_j2k->cstr_index->tile_index[p_j2k->m_current_tile_number].tp_index =
                    new_tp_index;
            }
        } else {
             {

                if (!p_j2k->cstr_index->tile_index[p_j2k->m_current_tile_number].tp_index) {
                    p_j2k->cstr_index->tile_index[p_j2k->m_current_tile_number].current_nb_tps = 10;
                    p_j2k->cstr_index->tile_index[p_j2k->m_current_tile_number].tp_index =
                        (opj_tp_index_t*)opj_calloc(
                            p_j2k->cstr_index->tile_index[p_j2k->m_current_tile_number].current_nb_tps,
                            sizeof(opj_tp_index_t));
                    if (!p_j2k->cstr_index->tile_index[p_j2k->m_current_tile_number].tp_index) {
                        p_j2k->cstr_index->tile_index[p_j2k->m_current_tile_number].current_nb_tps = 0;
                        opj_event_msg(p_manager, EVT_ERROR,
                                      "Not enough memory to read SOT marker. Tile index allocation failed\n");
                        return OPJ_FALSE;
                    }
                }

                if (l_current_part >=
                        p_j2k->cstr_index->tile_index[p_j2k->m_current_tile_number].current_nb_tps) {
                    opj_tp_index_t *new_tp_index;
                    p_j2k->cstr_index->tile_index[p_j2k->m_current_tile_number].current_nb_tps =
                        l_current_part + 1;
                    new_tp_index = (opj_tp_index_t *) opj_realloc(
                                       p_j2k->cstr_index->tile_index[p_j2k->m_current_tile_number].tp_index,
                                       p_j2k->cstr_index->tile_index[p_j2k->m_current_tile_number].current_nb_tps *
                                       sizeof(opj_tp_index_t));
                    if (! new_tp_index) {
                        opj_free(p_j2k->cstr_index->tile_index[p_j2k->m_current_tile_number].tp_index);
                        p_j2k->cstr_index->tile_index[p_j2k->m_current_tile_number].tp_index = NULL;
                        p_j2k->cstr_index->tile_index[p_j2k->m_current_tile_number].current_nb_tps = 0;
                        opj_event_msg(p_manager, EVT_ERROR,
                                      "Not enough memory to read SOT marker. Tile index allocation failed\n");
                        return OPJ_FALSE;
                    }
                    p_j2k->cstr_index->tile_index[p_j2k->m_current_tile_number].tp_index =
                        new_tp_index;
                }
            }

        }

    }


    return OPJ_TRUE;
}
