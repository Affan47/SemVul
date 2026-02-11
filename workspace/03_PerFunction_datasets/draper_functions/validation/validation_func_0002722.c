H5P__iterate_plist_pclass_cb(void *_item, void *_key, void *_udata)
{
    H5P_genprop_t *item = (H5P_genprop_t *)_item;
    char *key = (char *)_key;
    H5P_iter_plist_ud_t *udata = (H5P_iter_plist_ud_t *)_udata;
    int ret_value = H5_ITER_CONT;

    FUNC_ENTER_STATIC_NOERR


    HDassert(item);
    HDassert(key);


    if(NULL == H5SL_search(udata->seen, key) &&
            NULL == H5SL_search(udata->plist->del, key))
        ret_value = H5P__iterate_plist_cb(item, key, udata);

    FUNC_LEAVE_NOAPI(ret_value)
}
