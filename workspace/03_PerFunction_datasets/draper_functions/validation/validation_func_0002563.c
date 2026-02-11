H5D__chunk_lookup(const H5D_t *dset, hid_t dxpl_id, const hsize_t *chunk_offset,
    hsize_t chunk_idx, H5D_chunk_ud_t *udata)
{
    H5D_rdcc_ent_t  *ent = NULL;
    hbool_t         found = FALSE;
    unsigned        u;
    herr_t	ret_value = SUCCEED;

    FUNC_ENTER_PACKAGE

    HDassert(dset);
    HDassert(dset->shared->layout.u.chunk.ndims > 0);
    HDassert(chunk_offset);
    HDassert(udata);


    udata->common.layout = &(dset->shared->layout.u.chunk);
    udata->common.storage = &(dset->shared->layout.storage.u.chunk);
    udata->common.offset = chunk_offset;
    udata->common.rdcc = &(dset->shared->cache.chunk);


    udata->nbytes = 0;
    udata->filter_mask = 0;
    udata->addr = HADDR_UNDEF;


    if(dset->shared->cache.chunk.nslots > 0) {
        udata->idx_hint = H5D_CHUNK_HASH(dset->shared, chunk_idx);
        ent = dset->shared->cache.chunk.slot[udata->idx_hint];

        if(ent)
            for(u = 0, found = TRUE; u < dset->shared->layout.u.chunk.ndims - 1;
                    u++)
                if(chunk_offset[u] != ent->offset[u]) {
                    found = FALSE;
                    break;
                }
    }


    if(found)
        udata->addr = ent->chunk_addr;
    else {

        udata->idx_hint = UINT_MAX;


        if(!H5D__chunk_cinfo_cache_found(&dset->shared->cache.chunk.last, udata)) {
            H5D_chk_idx_info_t idx_info;


            idx_info.f = dset->oloc.file;
            idx_info.dxpl_id = dxpl_id;
            idx_info.pline = &dset->shared->dcpl_cache.pline;
            idx_info.layout = &dset->shared->layout.u.chunk;
            idx_info.storage = &dset->shared->layout.storage.u.chunk;


            if((dset->shared->layout.storage.u.chunk.ops->get_addr)(&idx_info, udata) < 0)
                HGOTO_ERROR(H5E_DATASET, H5E_CANTGET, FAIL, "can't query chunk address")


            H5D__chunk_cinfo_cache_update(&dset->shared->cache.chunk.last, udata);
        }
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
