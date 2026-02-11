H5HF_man_dblock_locate(H5HF_hdr_t *hdr, hid_t dxpl_id, hsize_t obj_off,
    H5HF_indirect_t **ret_iblock, unsigned *ret_entry, hbool_t *ret_did_protect,
    H5AC_protect_t rw)
{
    haddr_t iblock_addr;
    H5HF_indirect_t *iblock;
    hbool_t did_protect;
    unsigned row, col;
    unsigned entry;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(hdr);
    HDassert(hdr->man_dtable.curr_root_rows);
    HDassert(ret_iblock);
    HDassert(ret_did_protect);


    if(H5HF_dtable_lookup(&hdr->man_dtable, obj_off, &row, &col) < 0)
        HGOTO_ERROR(H5E_HEAP, H5E_CANTCOMPUTE, FAIL, "can't compute row & column of object")


    iblock_addr = hdr->man_dtable.table_addr;


    if(NULL == (iblock = H5HF_man_iblock_protect(hdr, dxpl_id, iblock_addr, hdr->man_dtable.curr_root_rows, NULL, 0, FALSE, rw, &did_protect)))
        HGOTO_ERROR(H5E_HEAP, H5E_CANTPROTECT, FAIL, "unable to protect fractal heap indirect block")


    while(row >= hdr->man_dtable.max_direct_rows) {
        H5HF_indirect_t *new_iblock;
        hbool_t new_did_protect;
        unsigned nrows;
        unsigned cache_flags = H5AC__NO_FLAGS_SET;


        nrows = (H5V_log2_gen(hdr->man_dtable.row_block_size[row]) - hdr->man_dtable.first_row_bits) + 1;
        HDassert(nrows < iblock->nrows);


        entry = (row * hdr->man_dtable.cparam.width) + col;


        iblock_addr = iblock->ents[entry].addr;


        if(!H5F_addr_defined(iblock_addr)) {
            if(H5HF_man_iblock_create(hdr, dxpl_id, iblock, entry, nrows, nrows, &iblock_addr) < 0)
                HGOTO_ERROR(H5E_HEAP, H5E_CANTALLOC, FAIL, "can't allocate fractal heap indirect block")


            cache_flags |= H5AC__DIRTIED_FLAG;
        }


        if(NULL == (new_iblock = H5HF_man_iblock_protect(hdr, dxpl_id, iblock_addr, nrows, iblock, entry, FALSE, rw, &new_did_protect)))
            HGOTO_ERROR(H5E_HEAP, H5E_CANTPROTECT, FAIL, "unable to protect fractal heap indirect block")


        if(H5HF_man_iblock_unprotect(iblock, dxpl_id, cache_flags, did_protect) < 0)
            HGOTO_ERROR(H5E_HEAP, H5E_CANTUNPROTECT, FAIL, "unable to release fractal heap indirect block")


        iblock = new_iblock;
        did_protect = new_did_protect;


        if(H5HF_dtable_lookup(&hdr->man_dtable, (obj_off - iblock->block_off), &row, &col) < 0)
            HGOTO_ERROR(H5E_HEAP, H5E_CANTCOMPUTE, FAIL, "can't compute row & column of object")
        HDassert(row < iblock->nrows);
    }


    if(ret_entry)
        *ret_entry = (row * hdr->man_dtable.cparam.width) + col;
    *ret_iblock = iblock;
    *ret_did_protect = did_protect;

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
