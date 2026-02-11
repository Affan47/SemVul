H5Tcommit_anon(hid_t loc_id, hid_t type_id, hid_t tcpl_id, hid_t tapl_id)
{
    H5G_loc_t	loc;
    H5T_t	*type = NULL;
    herr_t      ret_value = SUCCEED;

    FUNC_ENTER_API(FAIL)
    H5TRACE4("e", "iiii", loc_id, type_id, tcpl_id, tapl_id);


    if(H5G_loc(loc_id, &loc) < 0)
	HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a location")
    if(NULL == (type = (H5T_t *)H5I_object_verify(type_id, H5I_DATATYPE)))
	HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a datatype")


    if(H5P_DEFAULT == tcpl_id)
        tcpl_id = H5P_DATATYPE_CREATE_DEFAULT;
    else
        if(TRUE != H5P_isa_class(tcpl_id, H5P_DATATYPE_CREATE))
            HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not datatype creation property list")


    if(H5P_DEFAULT == tapl_id)
        tapl_id = H5P_DATATYPE_ACCESS_DEFAULT;
    else
        if(TRUE != H5P_isa_class(tapl_id, H5P_DATATYPE_ACCESS))
            HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not datatype access property list")


    if(H5T__commit(loc.oloc->file, type, tcpl_id, H5AC_dxpl_id) < 0)
	HGOTO_ERROR(H5E_DATATYPE, H5E_CANTINIT, FAIL, "unable to commit datatype")


    {
        H5O_loc_t *oloc;


        if(NULL == (oloc = H5T_oloc(type)))
            HGOTO_ERROR(H5E_DATATYPE, H5E_CANTGET, FAIL, "unable to get object location of committed datatype")


        if(H5O_dec_rc_by_loc(oloc, H5AC_dxpl_id) < 0)
           HGOTO_ERROR(H5E_DATATYPE, H5E_CANTDEC, FAIL, "unable to decrement refcount on newly created object")
    }

done:
    FUNC_LEAVE_API(ret_value)
}
