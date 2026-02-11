getp_intersect(VMG_ vm_val_t *retval,
                               const vm_val_t *self_val,
                               const char *lst, uint *argc)
{
    vm_val_t val2;
    vm_obj_id_t obj;
    static CVmNativeCodeDesc desc(1);


    if (get_prop_check_argc(retval, argc, &desc))
        return TRUE;


    val2 = *G_stk->get(0);


    G_stk->push(self_val);


    if (val2.get_as_list(vmg0_) == 0)
        err_throw(VMERR_LIST_VAL_REQD);


    obj = intersect(vmg_ self_val, &val2);


    G_stk->discard(2);


    retval->set_obj(obj);


    return TRUE;
}
