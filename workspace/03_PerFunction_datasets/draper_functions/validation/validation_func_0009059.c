H5Pget_size(hid_t id, const char *name, size_t *size)
{
    H5P_genclass_t	*pclass;
    H5P_genplist_t	*plist;
    herr_t ret_value;

    FUNC_ENTER_API(H5Pget_size, FAIL);
    H5TRACE3("e", "i*s*z", id, name, size);


    if(H5I_GENPROP_LST != H5I_get_type(id) && H5I_GENPROP_CLS != H5I_get_type(id))
        HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a property object");
    if(!name || !*name)
        HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "invalid property name");
    if(size==NULL)
        HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "invalid property size");

    if(H5I_GENPROP_LST == H5I_get_type(id)) {
        if(NULL == (plist = (H5P_genplist_t *)H5I_object(id)))
            HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a property list");


        if((ret_value = H5P_get_size_plist(plist, name, size)) < 0)
            HGOTO_ERROR(H5E_PLIST, H5E_CANTREGISTER, FAIL, "unable to query size in plist");
    }
    else
        if(H5I_GENPROP_CLS == H5I_get_type(id)) {
            if(NULL == (pclass = (H5P_genclass_t *)H5I_object(id)))
                HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a property list");


            if((ret_value = H5P_get_size_pclass(pclass, name, size)) < 0)
                HGOTO_ERROR(H5E_PLIST, H5E_CANTREGISTER, FAIL, "unable to query size in plist");
        }
        else
            HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a property object");

done:
    FUNC_LEAVE_API(ret_value);
}
