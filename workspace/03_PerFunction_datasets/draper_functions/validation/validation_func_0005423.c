mca_base_var_init(void)
{
    int ret;

    if (!mca_base_var_initialized) {


        OBJ_CONSTRUCT(&mca_base_vars, opal_pointer_array_t);

        ret = opal_pointer_array_init (&mca_base_vars, 128, 16384, 128);
        if (OPAL_SUCCESS != ret) {
            return ret;
        }

        mca_base_var_count = 0;


        OBJ_CONSTRUCT(&mca_base_var_file_values, opal_list_t);
        OBJ_CONSTRUCT(&mca_base_var_override_values, opal_list_t);
        OBJ_CONSTRUCT(&mca_base_var_index_hash, opal_hash_table_t);

        ret = opal_hash_table_init (&mca_base_var_index_hash, 1024);
        if (OPAL_SUCCESS != ret) {
            return ret;
        }

        ret = mca_base_var_group_init ();
        if  (OPAL_SUCCESS != ret) {
            return ret;
        }

        ret = mca_base_pvar_init ();
        if (OPAL_SUCCESS != ret) {
            return ret;
        }


        mca_base_var_initialized = true;

        mca_base_var_cache_files(false);
    }

    return OPAL_SUCCESS;
}
