static OPJ_BOOL opj_j2k_calculate_tp(opj_j2k_t *p_j2k,
                                     opj_cp_t *cp,
                                     OPJ_UINT32 * p_nb_tiles,
                                     opj_image_t *image,
                                     opj_event_mgr_t * p_manager
                                    )
{
    OPJ_UINT32 pino, tileno;
    OPJ_UINT32 l_nb_tiles;
    opj_tcp_t *tcp;


    assert(p_nb_tiles != 00);
    assert(cp != 00);
    assert(image != 00);
    assert(p_j2k != 00);
    assert(p_manager != 00);

    OPJ_UNUSED(p_j2k);
    OPJ_UNUSED(p_manager);

    l_nb_tiles = cp->tw * cp->th;
    * p_nb_tiles = 0;
    tcp = cp->tcps;


{
        for (tileno = 0; tileno < l_nb_tiles; ++tileno) {
            OPJ_UINT32 cur_totnum_tp = 0;

            opj_pi_update_encoding_parameters(image, cp, tileno);

            for (pino = 0; pino <= tcp->numpocs; ++pino) {
                OPJ_UINT32 tp_num = opj_j2k_get_num_tp(cp, pino, tileno);

                *p_nb_tiles = *p_nb_tiles + tp_num;

                cur_totnum_tp += tp_num;
            }
            tcp->m_nb_tile_parts = cur_totnum_tp;

            ++tcp;
        }
    }

    return OPJ_TRUE;
}
