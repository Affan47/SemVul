H5D__chunk_delete(H5F_t *f, hid_t dxpl_id, H5O_t *oh, H5O_storage_t *storage)
{
    H5D_chk_idx_info_t idx_info;
    H5O_layout_t layout;
    hbool_t layout_read = FALSE;
    H5O_pline_t pline;
    hbool_t pline_read = FALSE;
    htri_t	exists;
    herr_t      ret_value = SUCCEED;

    FUNC_ENTER_PACKAGE


    HDassert(f);
    HDassert(oh);
    HDassert(storage);


    if((exists = H5O_msg_exists_oh(oh, H5O_PLINE_ID)) < 0)
        HGOTO_ERROR(H5E_DATASET, H5E_CANTINIT, FAIL, "unable to check for object header message")
    else if(exists) {
        if(NULL == H5O_msg_read_oh(f, dxpl_id, oh, H5O_PLINE_ID, &pline))
            HGOTO_ERROR(H5E_DATASET, H5E_CANTGET, FAIL, "can't get I/O pipeline message")
        pline_read = TRUE;
    }
    else
        HDmemset(&pline, 0, sizeof(pline));


    if((exists = H5O_msg_exists_oh(oh, H5O_LAYOUT_ID)) < 0)
        HGOTO_ERROR(H5E_DATASET, H5E_CANTINIT, FAIL, "unable to check for object header message")
    else if(exists) {
        if(NULL == H5O_msg_read_oh(f, dxpl_id, oh, H5O_LAYOUT_ID, &layout))
            HGOTO_ERROR(H5E_DATASET, H5E_CANTGET, FAIL, "can't get layout message")
        layout_read = TRUE;
    }
    else
        HGOTO_ERROR(H5E_DATASET, H5E_NOTFOUND, FAIL, "can't find layout message")


    idx_info.f = f;
    idx_info.dxpl_id = dxpl_id;
    idx_info.pline = &pline;
    idx_info.layout = &layout.u.chunk;
    idx_info.storage = &storage->u.chunk;


    if((storage->u.chunk.ops->idx_delete)(&idx_info) < 0)
        HGOTO_ERROR(H5E_DATASET, H5E_CANTDELETE, FAIL, "unable to delete chunk index")

done:

    if(pline_read)
        if(H5O_msg_reset(H5O_PLINE_ID, &pline) < 0)
            HDONE_ERROR(H5E_DATASET, H5E_CANTRESET, FAIL, "unable to reset I/O pipeline message")
    if(layout_read)
        if(H5O_msg_reset(H5O_LAYOUT_ID, &layout) < 0)
            HDONE_ERROR(H5E_DATASET, H5E_CANTRESET, FAIL, "unable to reset layout message")

    FUNC_LEAVE_NOAPI(ret_value)
}
