static OPJ_UINT32 opj_j2k_get_specific_header_sizes(opj_j2k_t *p_j2k)
{
    OPJ_UINT32 l_nb_bytes = 0;
    OPJ_UINT32 l_nb_comps;
    OPJ_UINT32 l_coc_bytes, l_qcc_bytes;

    l_nb_comps = p_j2k->m_private_image->numcomps - 1;
    l_nb_bytes += opj_j2k_get_max_toc_size(p_j2k);

    if (!(OPJ_IS_CINEMA(p_j2k->m_cp.rsiz))) {
        l_coc_bytes = opj_j2k_get_max_coc_size(p_j2k);
        l_nb_bytes += l_nb_comps * l_coc_bytes;

        l_qcc_bytes = opj_j2k_get_max_qcc_size(p_j2k);
        l_nb_bytes += l_nb_comps * l_qcc_bytes;
    }

    l_nb_bytes += opj_j2k_get_max_poc_size(p_j2k);

    if (p_j2k->m_specific_param.m_encoder.m_PLT) {


        OPJ_UINT32 i;
        const opj_cp_t * l_cp = &(p_j2k->m_cp);
        OPJ_UINT32 l_max_packet_count = 0;
        for (i = 0; i < l_cp->th * l_cp->tw; ++i) {
            l_max_packet_count = opj_uint_max(l_max_packet_count,
                                              opj_get_encoding_packet_count(p_j2k->m_private_image, l_cp, i));
        }


        p_j2k->m_specific_param.m_encoder.m_reserved_bytes_for_PLT =
            6 * opj_uint_ceildiv(l_max_packet_count, 16382);

        p_j2k->m_specific_param.m_encoder.m_reserved_bytes_for_PLT +=
            l_nb_bytes += 5 * l_max_packet_count;
        p_j2k->m_specific_param.m_encoder.m_reserved_bytes_for_PLT += 1;
        l_nb_bytes += p_j2k->m_specific_param.m_encoder.m_reserved_bytes_for_PLT;
    }


    return l_nb_bytes;
}
