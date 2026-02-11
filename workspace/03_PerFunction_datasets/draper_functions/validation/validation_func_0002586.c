del_objs(H5F_t *f, hid_t dxpl, H5HF_t **fh, fheap_test_param_t *tparam,
    fheap_heap_state_t *state, fheap_heap_ids_t *keep_ids)
{
    haddr_t fh_addr = HADDR_UNDEF;
    size_t id_len;
    size_t obj_idx;
    size_t u;


    HDassert(fh);
    HDassert(*fh);
    HDassert(state);
    HDassert(keep_ids);


    if(tparam->drain_half == FHEAP_DEL_DRAIN_HALF)
        if(del_objs_half_refill(f, dxpl, fh, tparam, keep_ids))
            TEST_ERROR


    if(tparam->reopen_heap) {
        if(H5HF_get_heap_addr(*fh, &fh_addr) < 0)
            FAIL_STACK_ERROR
        if(!H5F_addr_defined(fh_addr))
            TEST_ERROR
    }


    if(H5HF_get_id_len(*fh, &id_len) < 0)
        FAIL_STACK_ERROR


    if(tparam->del_dir == FHEAP_DEL_FORWARD)
        obj_idx = 0;
    else
        obj_idx = keep_ids->num_ids - 1;
    for(u = 0; u < keep_ids->num_ids; u++) {

        if(H5HF_remove(*fh, dxpl, &keep_ids->ids[id_len * obj_idx]) < 0)
            FAIL_STACK_ERROR


        if(reopen_heap(f, dxpl, fh, fh_addr, tparam) < 0)
            TEST_ERROR


        if(tparam->del_dir == FHEAP_DEL_FORWARD)
            obj_idx++;
        else
            obj_idx--;
    }


    HDmemset(state, 0, sizeof(fheap_heap_state_t));


    if(check_stats(*fh, state))
        TEST_ERROR


    return(0);

error:
    return(1);
}
