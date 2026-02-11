getp_abs(VMG_ vm_obj_id_t self,
                           vm_val_t *retval, uint *argc)
{
    char *new_ext;
    size_t prec = get_prec(ext_);
    static CVmNativeCodeDesc desc(0);


    if (get_prop_check_argc(retval, argc, &desc))
        return TRUE;


    if (!get_neg(ext_)
        || (get_type(ext_) != VMBN_T_NUM && get_type(ext_) != VMBN_T_INF))
    {
        retval->set_obj(self);
        return TRUE;
    }


    G_stk->push()->set_obj(self);


    if (get_type(ext_) == VMBN_T_INF)
        prec = 1;


    retval->set_obj(create(vmg_ FALSE, prec));
    new_ext = get_objid_ext(vmg_ retval->val.obj);


    memcpy(new_ext, ext_, calc_alloc(prec));


    set_neg(new_ext, FALSE);


    G_stk->discard();


    return TRUE;
}
