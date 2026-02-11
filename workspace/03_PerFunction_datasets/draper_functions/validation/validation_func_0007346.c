memheap_oob_get_mkeys(int pe, uint32_t seg, sshmem_mkey_t *mkeys)
{
    opal_buffer_t *msg;
    uint8_t cmd;
    int i;
    int rc;

    if (OSHMEM_SUCCESS == MCA_SPML_CALL(oob_get_mkeys(pe, seg, mkeys))) {
        for (i = 0; i < memheap_map->num_transports; i++) {
            mkeys[i].va_base = __seg2base_va(seg);
            MEMHEAP_VERBOSE(5,
                            "MKEY CALCULATED BY LOCAL SPML: pe: %d tr_id: %d %s",
                            pe,
                            i,
                            mca_spml_base_mkey2str(&mkeys[i]));
        }
        return OSHMEM_SUCCESS;
    }

    OPAL_THREAD_LOCK(&memheap_oob.lck);

    memheap_oob.mkeys = mkeys;
    memheap_oob.mkeys_rcvd = 0;

    msg = OBJ_NEW(opal_buffer_t);
    if (!msg) {
        OPAL_THREAD_UNLOCK(&memheap_oob.lck);
        MEMHEAP_ERROR("failed to get msg buffer");
        return OSHMEM_ERROR;
    }

    OPAL_THREAD_LOCK(&memheap_oob.lck);
    cmd = MEMHEAP_RKEY_REQ;
    opal_dss.pack(msg, &cmd, 1, OPAL_UINT8);
    opal_dss.pack(msg, &seg, 1, OPAL_UINT32);

    rc = send_buffer(pe, msg);
    if (MPI_SUCCESS != rc) {
        OPAL_THREAD_UNLOCK(&memheap_oob.lck);
        MEMHEAP_ERROR("FAILED to send rml message %d", rc);
        return OSHMEM_ERROR;
    }

    while (!memheap_oob.mkeys_rcvd) {
        opal_condition_wait(&memheap_oob.cond, &memheap_oob.lck);
    }

    if (MEMHEAP_RKEY_RESP == memheap_oob.mkeys_rcvd) {
        rc = OSHMEM_SUCCESS;
    } else {
        MEMHEAP_ERROR("failed to get rkey seg#%d pe=%d", seg, pe);
        rc = OSHMEM_ERROR;
    }

    OPAL_THREAD_UNLOCK(&memheap_oob.lck);
    return rc;
}
