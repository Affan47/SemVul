H5P__set_filter(H5P_genplist_t *plist, H5Z_filter_t filter, unsigned int flags,
	       size_t cd_nelmts, const unsigned int cd_values[])
{
    H5O_pline_t     pline;
    htri_t          filter_avail;
    herr_t          ret_value = SUCCEED;

    FUNC_ENTER_STATIC


    if((filter_avail = H5Z_filter_avail(filter)) < 0)
        HGOTO_ERROR(H5E_PLIST, H5E_CANTSET, FAIL, "can't check filter availability")


    if(!filter_avail) {
        const H5Z_class2_t *filter_info;

        if(NULL == (filter_info = (const H5Z_class2_t *)H5PL_load(H5PL_TYPE_FILTER, (int)filter)))
            HGOTO_ERROR(H5E_PLINE, H5E_CANTLOAD, FAIL, "failed to load dynamically loaded plugin")
        if(H5Z_register(filter_info) < 0)
	    HGOTO_ERROR(H5E_PLINE, H5E_CANTINIT, FAIL, "unable to register filter")
    }


    if(H5P_get(plist, H5O_CRT_PIPELINE_NAME, &pline) < 0)
        HGOTO_ERROR(H5E_PLIST, H5E_CANTGET, FAIL, "can't get pipeline")


    if(H5Z_append(&pline, filter, flags, cd_nelmts, cd_values) < 0)
        HGOTO_ERROR(H5E_PLINE, H5E_CANTINIT, FAIL, "unable to add filter to pipeline")


    if(H5P_set(plist, H5O_CRT_PIPELINE_NAME, &pline) < 0)
        HGOTO_ERROR(H5E_PLIST, H5E_CANTSET, FAIL, "can't set pipeline")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
