getp_match_values(VMG_ vm_obj_id_t ,
                                     vm_val_t *retval, uint *argc)
{
    static CVmNativeCodeDesc desc(2);
    const char *valstr;
    const char *refstr;


    if (get_prop_check_argc(retval, argc, &desc))
        return TRUE;


    valstr = G_stk->get(0)->get_as_string(vmg0_);
    refstr = G_stk->get(1)->get_as_string(vmg0_);


    if (valstr == 0 || refstr == 0)
        err_throw(VMERR_BAD_TYPE_BIF);


    retval->set_int(match_strings(valstr + VMB_LEN, vmb_get_len(valstr),
                                  refstr + VMB_LEN, vmb_get_len(refstr)));


    G_stk->discard(2);


    return TRUE;
}
