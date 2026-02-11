bf_set_verb_args(Var arglist, Byte next, void *vdata, Objid progr)
{
    Objid oid = arglist.v.list[1].v.obj;
    Var desc = arglist.v.list[2];
    Var args = arglist.v.list[3];
    enum error e;
    db_verb_handle h;
    db_arg_spec dobj, iobj;
    db_prep_spec prep;

    if ((e = validate_verb_descriptor(desc)) != E_NONE);
    else if (!valid(oid))
	e = E_INVARG;
    else
	e = validate_verb_args(args, &dobj, &prep, &iobj);

    if (e != E_NONE) {
	free_var(arglist);
	return make_error_pack(e);
    }
    h = find_described_verb(oid, desc);
    free_var(arglist);

    if (!h.ptr)
	return make_error_pack(E_VERBNF);
    else if (!db_verb_allows(h, progr, VF_WRITE))
	return make_error_pack(E_PERM);

    db_set_verb_arg_specs(h, dobj, prep, iobj);

    return no_var_pack();
}
