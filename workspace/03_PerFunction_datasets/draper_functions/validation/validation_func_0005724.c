H5O_alloc_null(H5F_t *f, hid_t dxpl_id, H5O_t *oh, size_t null_idx,
    const H5O_msg_class_t *new_type, void *new_native, size_t new_size)
{
    H5O_chunk_proxy_t *chk_proxy = NULL;
    hbool_t chk_dirtied = FALSE;
    H5O_mesg_t *alloc_msg;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(oh);
    HDassert(new_type);
    HDassert(new_size);


    alloc_msg = &oh->mesg[null_idx];


    if(NULL == (chk_proxy = H5O_chunk_protect(f, dxpl_id, oh, alloc_msg->chunkno)))
        HGOTO_ERROR(H5E_OHDR, H5E_CANTPROTECT, FAIL, "unable to load object header chunk")


    if(alloc_msg->raw_size > new_size) {

        if((alloc_msg->raw_size - new_size) < (size_t)H5O_SIZEOF_MSGHDR_OH(oh)) {
            size_t gap_size = alloc_msg->raw_size - new_size;


            alloc_msg->raw_size = new_size;


            if(H5O_add_gap(f, oh, alloc_msg->chunkno, &chk_dirtied, null_idx, alloc_msg->raw + alloc_msg->raw_size, gap_size) < 0)
                HGOTO_ERROR(H5E_OHDR, H5E_CANTINSERT, FAIL, "can't insert gap in chunk")
        }
        else {
            size_t  new_mesg_size = new_size + (size_t)H5O_SIZEOF_MSGHDR_OH(oh);
            H5O_mesg_t *null_msg;


            if(oh->nmesgs >= oh->alloc_nmesgs) {
                if(H5O_alloc_msgs(oh, (size_t)1) < 0)
                    HGOTO_ERROR(H5E_RESOURCE, H5E_NOSPACE, FAIL, "can't allocate more space for messages")


                alloc_msg = &oh->mesg[null_idx];
            }


            null_msg = &(oh->mesg[oh->nmesgs++]);
            null_msg->type = H5O_MSG_NULL;
            null_msg->native = NULL;
            null_msg->raw = alloc_msg->raw + new_mesg_size;
            null_msg->raw_size = alloc_msg->raw_size - new_mesg_size;
            null_msg->chunkno = alloc_msg->chunkno;


            null_msg->dirty = TRUE;
            chk_dirtied = TRUE;


            if(oh->chunk[null_msg->chunkno].gap > 0) {
                unsigned null_chunkno = null_msg->chunkno;


                if(H5O_eliminate_gap(oh, &chk_dirtied, null_msg,
                        ((oh->chunk[null_chunkno].image + oh->chunk[null_chunkno].size) - (H5O_SIZEOF_CHKSUM_OH(oh) + oh->chunk[null_chunkno].gap)),
                        oh->chunk[null_chunkno].gap) < 0)
                    HGOTO_ERROR(H5E_OHDR, H5E_CANTREMOVE, FAIL, "can't eliminate gap in chunk")
            }


            alloc_msg->raw_size = new_size;
        }
    }


    alloc_msg->type = new_type;
    alloc_msg->native = new_native;


    alloc_msg->dirty = TRUE;
    chk_dirtied = TRUE;

done:

    if(chk_proxy && H5O_chunk_unprotect(f, dxpl_id, chk_proxy, chk_dirtied) < 0)
        HDONE_ERROR(H5E_OHDR, H5E_CANTUNPROTECT, FAIL, "unable to unprotect object header chunk")

    FUNC_LEAVE_NOAPI(ret_value)
}
