H5SM_delete(H5F_t *f, hid_t dxpl_id, H5O_t *open_oh, H5O_shared_t *sh_mesg)
{
    H5SM_master_table_t  *table = NULL;
    unsigned              cache_flags = H5AC__NO_FLAGS_SET;
    H5SM_table_cache_ud_t cache_udata;
    ssize_t               index_num;
    void                 *mesg_buf = NULL;
    void                 *native_mesg = NULL;
    unsigned              type_id;
    herr_t                ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(H5SM_delete, FAIL)

    HDassert(f);
    HDassert(f->shared->sohm_addr != HADDR_UNDEF);
    HDassert(sh_mesg);


    type_id = sh_mesg->msg_type_id;


    cache_udata.f = f;


    if(NULL == (table = (H5SM_master_table_t *)H5AC_protect(f, dxpl_id, H5AC_SOHM_TABLE, f->shared->sohm_addr, &cache_udata, H5AC_WRITE)))
	HGOTO_ERROR(H5E_SOHM, H5E_CANTPROTECT, FAIL, "unable to load SOHM master table")


    if((index_num = H5SM_get_index(table, type_id)) < 0)
	HGOTO_ERROR(H5E_SOHM, H5E_NOTFOUND, FAIL, "unable to find correct SOHM index")


    if(H5SM_delete_from_index(f, dxpl_id, open_oh, &(table->indexes[index_num]), sh_mesg, &cache_flags, &mesg_buf) < 0)
	HGOTO_ERROR(H5E_SOHM, H5E_CANTDELETE, FAIL, "unable to delete mesage from SOHM index")


    if(H5AC_unprotect(f, dxpl_id, H5AC_SOHM_TABLE, f->shared->sohm_addr, table, cache_flags) < 0)
	HGOTO_ERROR(H5E_SOHM, H5E_CANTUNPROTECT, FAIL, "unable to close SOHM master table")
    table = NULL;


    if(mesg_buf) {
        if(NULL == (native_mesg = H5O_msg_decode(f, dxpl_id, open_oh, type_id, (const unsigned char *)mesg_buf)))
            HGOTO_ERROR(H5E_SOHM, H5E_CANTDECODE, FAIL, "can't decode shared message.")

        if(H5O_msg_delete(f, dxpl_id, open_oh, type_id, native_mesg) < 0)
            HGOTO_ERROR(H5E_SOHM, H5E_CANTFREE, FAIL, "can't delete shared message.")
    }

done:

    if(table && H5AC_unprotect(f, dxpl_id, H5AC_SOHM_TABLE, f->shared->sohm_addr, table, cache_flags) < 0)
	HDONE_ERROR(H5E_SOHM, H5E_CANTUNPROTECT, FAIL, "unable to close SOHM master table")


    if(native_mesg)
        H5O_msg_free(type_id, native_mesg);


    if(mesg_buf)
        mesg_buf = H5MM_xfree(mesg_buf);

    FUNC_LEAVE_NOAPI(ret_value)
}
