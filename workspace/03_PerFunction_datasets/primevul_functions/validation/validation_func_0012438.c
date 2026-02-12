STATIC mse * GC_array_mark_proc(word * addr, mse * mark_stack_ptr,
                                mse * mark_stack_limit,
                                word env GC_ATTR_UNUSED)
{
    hdr * hhdr = HDR(addr);
    size_t sz = hhdr -> hb_sz;
    size_t nwords = BYTES_TO_WORDS(sz);
    complex_descriptor * descr = (complex_descriptor *)(addr[nwords-1]);
    mse * orig_mark_stack_ptr = mark_stack_ptr;
    mse * new_mark_stack_ptr;

    if (descr == 0) {

        return(orig_mark_stack_ptr);
    }


    new_mark_stack_ptr = GC_push_complex_descriptor(addr, descr,
                                                    mark_stack_ptr,
                                                    mark_stack_limit-1);
    if (new_mark_stack_ptr == 0) {


        GC_ASSERT(mark_stack_ptr != NULL);
        GC_mark_stack_too_small = TRUE;
        new_mark_stack_ptr = orig_mark_stack_ptr + 1;
        new_mark_stack_ptr -> mse_start = (ptr_t)addr;
        new_mark_stack_ptr -> mse_descr.w = sz | GC_DS_LENGTH;
    } else {

        new_mark_stack_ptr++;
        new_mark_stack_ptr -> mse_start = (ptr_t)(addr + nwords - 1);
        new_mark_stack_ptr -> mse_descr.w = sizeof(word) | GC_DS_LENGTH;
    }
    return new_mark_stack_ptr;
}
