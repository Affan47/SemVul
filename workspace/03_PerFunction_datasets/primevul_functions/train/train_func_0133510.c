OPJ_BOOL opj_j2k_read_header(   opj_stream_private_t *p_stream,
                                                            opj_j2k_t* p_j2k,
                                                            opj_image_t** p_image,
                                                            opj_event_mgr_t* p_manager )
{

        assert(p_j2k != 00);
        assert(p_stream != 00);
        assert(p_manager != 00);


        p_j2k->m_private_image = opj_image_create0();
        if (! p_j2k->m_private_image) {
                return OPJ_FALSE;
        }


        opj_j2k_setup_decoding_validation(p_j2k);


        if (! opj_j2k_exec(p_j2k, p_j2k->m_validation_list, p_stream,p_manager)) {
                opj_image_destroy(p_j2k->m_private_image);
                p_j2k->m_private_image = NULL;
                return OPJ_FALSE;
        }


        opj_j2k_setup_header_reading(p_j2k);


        if (! opj_j2k_exec (p_j2k,p_j2k->m_procedure_list,p_stream,p_manager)) {
                opj_image_destroy(p_j2k->m_private_image);
                p_j2k->m_private_image = NULL;
                return OPJ_FALSE;
        }

        *p_image = opj_image_create0();
        if (! (*p_image)) {
                return OPJ_FALSE;
        }


        opj_copy_image_header(p_j2k->m_private_image, *p_image);


        if (!opj_j2k_allocate_tile_element_cstr_index(p_j2k)){
                return OPJ_FALSE;
        }

        return OPJ_TRUE;
}
