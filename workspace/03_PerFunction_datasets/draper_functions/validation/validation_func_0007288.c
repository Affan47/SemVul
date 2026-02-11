afr_build_pending_matrix (char **pending_key, int32_t **pending_matrix,
                          unsigned char *ignorant_subvols,
                          dict_t *xattr[], afr_transaction_type type,
                          size_t child_count)
{

        int32_t        pending[3]       = {0,};
        void          *pending_raw      = NULL;
        int            ret              = -1;
        int            i                = 0;
        int            j                = 0;
        int            k                = 0;

        afr_init_pending_matrix (pending_matrix, child_count);

        for (i = 0; i < child_count; i++) {
                pending_raw = NULL;

                for (j = 0; j < child_count; j++) {
                        ret = dict_get_ptr (xattr[i], pending_key[j],
                                            &pending_raw);

                        if (ret != 0) {


                                if (ignorant_subvols)
                                        ignorant_subvols[i] = 1;
                                continue;
                        }

                        memcpy (pending, pending_raw, sizeof(pending));
                        k = afr_index_for_transaction_type (type);

                        pending_matrix[i][j] = ntoh32 (pending[k]);
                }
        }

        return ret;
}
