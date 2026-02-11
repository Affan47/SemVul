H5HF_sect_single_shrink(H5FS_section_info_t **_sect, void UNUSED *_udata)
{
    H5HF_free_section_t **sect = (H5HF_free_section_t **)_sect;
    H5HF_sect_add_ud1_t *udata = (H5HF_sect_add_ud1_t *)_udata;
    H5HF_hdr_t *hdr = udata->hdr;
    hid_t dxpl_id = udata->dxpl_id;
    H5HF_direct_t *dblock;
    haddr_t dblock_addr;
    size_t dblock_size;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT(H5HF_sect_single_shrink)


    HDassert(sect);
    HDassert(*sect);
    HDassert((*sect)->sect_info.type == H5HF_FSPACE_SECT_SINGLE);


    if((*sect)->sect_info.state != H5FS_SECT_LIVE)
        if(H5HF_sect_single_revive(hdr, dxpl_id, (*sect)) < 0)
            HGOTO_ERROR(H5E_HEAP, H5E_CANTINIT, FAIL, "can't revive single free section")


    if(H5HF_sect_single_dblock_info(hdr, dxpl_id, (*sect), &dblock_addr, &dblock_size) < 0)
        HGOTO_ERROR(H5E_HEAP, H5E_CANTGET, FAIL, "can't retrieve direct block information")


    HDassert(dblock_addr == hdr->man_dtable.table_addr);
    if(NULL == (dblock = H5HF_man_dblock_protect(hdr, dxpl_id, dblock_addr,
            dblock_size, (*sect)->u.single.parent, (*sect)->u.single.par_entry, H5AC_WRITE)))
        HGOTO_ERROR(H5E_HEAP, H5E_CANTPROTECT, FAIL, "unable to load fractal heap direct block")
    HDassert(H5F_addr_eq(dblock->block_off + dblock_size, (*sect)->sect_info.addr + (*sect)->sect_info.size));


    if(H5HF_man_dblock_destroy(hdr, dxpl_id, dblock, dblock_addr) < 0)
        HGOTO_ERROR(H5E_HEAP, H5E_CANTRELEASE, FAIL, "can't release direct block")
    dblock = NULL;


    if(H5HF_sect_single_free((H5FS_section_info_t *)*sect) < 0)
        HGOTO_ERROR(H5E_HEAP, H5E_CANTRELEASE, FAIL, "can't free section node")


    *sect = NULL;

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
