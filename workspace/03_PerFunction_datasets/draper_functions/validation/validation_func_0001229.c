H5O_touch_oh(H5F_t *f, hid_t dxpl_id, H5O_t *oh, hbool_t force)
{
    H5O_chunk_proxy_t *chk_proxy = NULL;
    hbool_t chk_dirtied = FALSE;
    time_t	now;
    herr_t      ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT(H5O_touch_oh)

    HDassert(f);
    HDassert(oh);


    if(oh->flags & H5O_HDR_STORE_TIMES) {

        now = H5_now();


        if(oh->version == H5O_VERSION_1) {
            int	idx;


            for(idx = 0; idx < (int)oh->nmesgs; idx++)
                if(H5O_MSG_MTIME == oh->mesg[idx].type || H5O_MSG_MTIME_NEW == oh->mesg[idx].type)
                    break;


            if(idx == (int)oh->nmesgs) {
                unsigned mesg_flags = 0;


                if(!force)
                    HGOTO_DONE(SUCCEED);


                if((idx = H5O_msg_alloc(f, dxpl_id, oh, H5O_MSG_MTIME_NEW, &mesg_flags, &now)) < 0)
                    HGOTO_ERROR(H5E_OHDR, H5E_CANTINIT, FAIL, "unable to allocate space for modification time message")


                oh->mesg[idx].flags = (uint8_t)mesg_flags;
            }


            if(NULL == (chk_proxy = H5O_chunk_protect(f, dxpl_id, oh, oh->mesg[idx].chunkno)))
                HGOTO_ERROR(H5E_OHDR, H5E_CANTPROTECT, FAIL, "unable to load object header chunk")


            if(NULL == oh->mesg[idx].native) {
                if(NULL == (oh->mesg[idx].native = H5FL_MALLOC(time_t)))
                    HGOTO_ERROR(H5E_OHDR, H5E_CANTINIT, FAIL, "memory allocation failed for modification time message")
            }


            *((time_t *)(oh->mesg[idx].native)) = now;


            oh->mesg[idx].dirty = TRUE;
            chk_dirtied = TRUE;
        }
        else {


            oh->atime = oh->ctime = now;


            if(H5AC_mark_entry_dirty(oh) < 0)
                HGOTO_ERROR(H5E_OHDR, H5E_CANTMARKDIRTY, FAIL, "unable to mark object header as dirty")
        }
    }

done:

    if(chk_proxy && H5O_chunk_unprotect(f, dxpl_id, chk_proxy, chk_dirtied) < 0)
        HDONE_ERROR(H5E_OHDR, H5E_CANTUNPROTECT, FAIL, "unable to unprotect object header chunk")

    FUNC_LEAVE_NOAPI(ret_value)
}
