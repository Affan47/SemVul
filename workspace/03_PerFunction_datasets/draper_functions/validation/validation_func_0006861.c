const_equals(VMG_ const vm_val_t *lstval, const char *lstmem,
                             const vm_val_t *val, int depth)
{
    const char *lstmem2;
    const vm_val_t *lstval2;
    size_t cnt;
    size_t idx;


    lstmem2 = val->get_as_list(vmg0_);
    lstval2 = val;


    if (lstmem2 == 0)
        return FALSE;


    cnt = vmb_get_len(lstmem);
    if (cnt != vmb_get_len(lstmem2))
        return FALSE;


    for (idx = 0 ; idx < cnt ; ++idx)
    {
        vm_val_t val1;
        vm_val_t val2;


        VM_IF_SWAPPING_POOL(if (lstval != 0 && lstval->typ == VM_LIST)
            lstmem = G_const_pool->get_ptr(lstval->val.ofs));
        VM_IF_SWAPPING_POOL(if (lstval2 != 0 && lstval2->typ == VM_LIST)
            lstmem2 = G_const_pool->get_ptr(lstval2->val.ofs));


        vmb_get_dh(get_element_ptr_const(lstmem, idx), &val1);
        vmb_get_dh(get_element_ptr_const(lstmem2, idx), &val2);


        if (!val1.equals(vmg_ &val2, depth))
            return FALSE;
    }


    return TRUE;
}
