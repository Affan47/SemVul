H5HF_sect_single_can_shrink(const H5FS_section_info_t *_sect, void *_udata)
{
    const H5HF_free_section_t *sect = (const H5HF_free_section_t *)_sect;
    H5HF_sect_add_ud_t *udata = (H5HF_sect_add_ud_t *)_udata;
    H5HF_hdr_t *hdr = udata->hdr;
    htri_t ret_value = FALSE;

    FUNC_ENTER_NOAPI_NOINIT_NOERR


    HDassert(sect);


    if(hdr->man_dtable.curr_root_rows == 0) {
        size_t dblock_size;
        size_t dblock_overhead;

        dblock_size = hdr->man_dtable.cparam.start_block_size;
        dblock_overhead = H5HF_MAN_ABS_DIRECT_OVERHEAD(hdr);
        if((dblock_size - dblock_overhead) == sect->sect_info.size)
            HGOTO_DONE(TRUE)
    }
    else {


        HDassert(hdr->man_iter_off > sect->sect_info.addr);
        HGOTO_DONE(FALSE)
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
