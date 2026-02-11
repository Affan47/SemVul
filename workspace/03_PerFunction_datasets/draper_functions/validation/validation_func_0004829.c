H5G_dense_btree2_corder_decode(const uint8_t *raw, void *_nrecord, void H5_ATTR_UNUSED *ctx)
{
    H5G_dense_bt2_corder_rec_t *nrecord = (H5G_dense_bt2_corder_rec_t *)_nrecord;

    FUNC_ENTER_NOAPI_NOINIT_NOERR


    INT64DECODE(raw, nrecord->corder)
    HDmemcpy(nrecord->id, raw, (size_t)H5G_DENSE_FHEAP_ID_LEN);

    FUNC_LEAVE_NOAPI(SUCCEED)
}
