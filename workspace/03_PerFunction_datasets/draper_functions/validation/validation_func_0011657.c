H5SL_new_node(void *item, const void *key, uint32_t hashval)
{
    H5SL_node_t *ret_value;

    FUNC_ENTER_NOAPI_NOINIT


    if(NULL == (ret_value = (H5SL_node_t *)H5FL_MALLOC(H5SL_node_t)))
        HGOTO_ERROR(H5E_SLIST, H5E_NOSPACE, NULL, "memory allocation failed")


    ret_value->key = key;
    ret_value->item = item;
    ret_value->level = 0;
    ret_value->hashval = hashval;
    ret_value->removed = FALSE;
    if(NULL == (ret_value->forward = (H5SL_node_t **)H5FL_FAC_MALLOC(H5SL_fac_g[0]))) {
        ret_value = H5FL_FREE(H5SL_node_t, ret_value);
        HGOTO_ERROR(H5E_SLIST, H5E_NOSPACE, NULL, "memory allocation failed")
    }
    ret_value->log_nalloc = 0;

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
