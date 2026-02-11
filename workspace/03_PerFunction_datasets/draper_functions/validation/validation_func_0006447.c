H5HG_link(H5F_t *f, hid_t dxpl_id, const H5HG_t *hobj, int adjust)
{
    H5HG_heap_t *heap = NULL;
    unsigned heap_flags = H5AC__NO_FLAGS_SET;
    int ret_value;

    FUNC_ENTER_NOAPI(FAIL)


    HDassert(f);
    HDassert(hobj);
    if(0 == (H5F_INTENT(f) & H5F_ACC_RDWR))
	HGOTO_ERROR(H5E_HEAP, H5E_WRITEERROR, FAIL, "no write intent on file")


    if(NULL == (heap = H5HG_protect(f, dxpl_id, hobj->addr, H5AC_WRITE)))
        HGOTO_ERROR(H5E_HEAP, H5E_CANTPROTECT, FAIL, "unable to protect global heap")

    if(adjust != 0) {
        HDassert(hobj->idx < heap->nused);
        HDassert(heap->obj[hobj->idx].begin);
        if((heap->obj[hobj->idx].nrefs + adjust) < 0)
            HGOTO_ERROR(H5E_HEAP, H5E_BADRANGE, FAIL, "new link count would be out of range")
        if((heap->obj[hobj->idx].nrefs + adjust) > H5HG_MAXLINK)
            HGOTO_ERROR(H5E_HEAP, H5E_BADVALUE, FAIL, "new link count would be out of range")
        heap->obj[hobj->idx].nrefs += adjust;
        heap_flags |= H5AC__DIRTIED_FLAG;
    }


    ret_value = heap->obj[hobj->idx].nrefs;

done:
    if(heap && H5AC_unprotect(f, dxpl_id, H5AC_GHEAP, hobj->addr, heap, heap_flags) < 0)
        HDONE_ERROR(H5E_HEAP, H5E_CANTUNPROTECT, FAIL, "unable to release object header")

    FUNC_LEAVE_NOAPI(ret_value)
}
