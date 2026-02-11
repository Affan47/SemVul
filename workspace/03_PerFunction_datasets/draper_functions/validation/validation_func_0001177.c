init_nb_coll_buff_desc(mca_bcol_basesmuma_nb_coll_buff_desc_t **desc,
				void *base_addr, uint32_t num_banks,
				uint32_t num_buffers_per_bank,
				uint32_t size_buffer,
				uint32_t header_size,
				int group_size,
				int pow_k)
{
    uint32_t i, j, ci;
    mca_bcol_basesmuma_nb_coll_buff_desc_t *tmp_desc = NULL;
    int k_nomial_radix = mca_bcol_basesmuma_component.k_nomial_radix;
    int pow_k_val = (0 == pow_k) ? 1 : pow_k;
    int num_to_alloc = (k_nomial_radix - 1) * pow_k_val * 2 + 1 ;


    *desc = (mca_bcol_basesmuma_nb_coll_buff_desc_t *)calloc(num_banks * num_buffers_per_bank, sizeof(mca_bcol_basesmuma_nb_coll_buff_desc_t));
    if (NULL == *desc) {
        return OMPI_ERROR;
    }

    tmp_desc = *desc;

    for (i = 0; i < num_banks; i++) {
        for (j = 0; j < num_buffers_per_bank; j++) {
            ci = i * num_buffers_per_bank + j;
            tmp_desc[ci].bank_index = i;
            tmp_desc[ci].buffer_index = j;

            tmp_desc[ci].requests = (ompi_request_t **)
                calloc(num_to_alloc, sizeof(ompi_request_t *));
            tmp_desc[ci].data_addr = (void *)
                ((unsigned char*)base_addr + ci * size_buffer + header_size);
            BASESMUMA_VERBOSE(10, ("ml memory cache setup %d %d - %p", i, j, tmp_desc[ci].data_addr));
        }
    }

    return OMPI_SUCCESS;
}
