validate_verb_args(Var v, db_arg_spec * dobj, db_prep_spec * prep,
		   db_arg_spec * iobj)
{
    if (!(v.type == TYPE_LIST
	  && v.v.list[0].v.num == 3
	  && v.v.list[1].type == TYPE_STR
	  && v.v.list[2].type == TYPE_STR
	  && v.v.list[3].type == TYPE_STR))
	return E_TYPE;

    if (!match_arg_spec(v.v.list[1].v.str, dobj)
	|| !match_prep_spec(v.v.list[2].v.str, prep)
	|| !match_arg_spec(v.v.list[3].v.str, iobj))
	return E_INVARG;

    return E_NONE;
}
