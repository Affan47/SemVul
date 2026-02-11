H5F_check_cached_stab_test(hid_t file_id)
{
    H5F_t	*file;
    herr_t	ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    if(NULL == (file = (H5F_t *)H5I_object_verify(file_id, H5I_FILE)))
	HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a file")


    if(H5G__verify_cached_stab_test(H5G_oloc(file->shared->root_grp), file->shared->sblock->root_ent) < 0)
        HGOTO_ERROR(H5E_FILE, H5E_CANTGET, FAIL, "unable to verify cached symbol table info")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
