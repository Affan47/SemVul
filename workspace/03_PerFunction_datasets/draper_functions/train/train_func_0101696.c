H5O_close(H5O_loc_t *loc)
{
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(FAIL)


    HDassert(loc);
    HDassert(loc->file);
    HDassert(H5F_NOPEN_OBJS(loc->file) > 0);


    H5F_DECR_NOPEN_OBJS(loc->file);

#ifdef H5O_DEBUG
    if(H5DEBUG(O)) {
	if(H5F_FILE_ID(loc->file)< 0 && 1 == H5F_NREFS(loc->file))
	    HDfprintf(H5DEBUG(O), "< %a auto %lu remaining\n",
		      loc->addr,
		      (unsigned long)H5F_NOPEN_OBJS(loc->file));
	else
	    HDfprintf(H5DEBUG(O), "< %a\n", loc->addr);
    }
#endif


    if(H5F_NOPEN_OBJS(loc->file) == H5F_NMOUNTS(loc->file))

        if(H5F_try_close(loc->file) < 0)
            HGOTO_ERROR(H5E_OHDR, H5E_CANTCLOSEFILE, FAIL, "problem attempting file close")


    if(H5O_loc_free(loc) < 0)
        HGOTO_ERROR(H5E_OHDR, H5E_CANTRELEASE, FAIL, "problem attempting to free location")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
