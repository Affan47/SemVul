bool_on_stack(cctx_T *cctx)
{
    type_T	*type;

    type = get_type_on_stack(cctx, 0);
    if (type == &t_bool)
	return OK;

    if (type == &t_any
	    || type == &t_unknown
	    || type == &t_number
	    || type == &t_number_bool)


	return generate_COND2BOOL(cctx);

    return need_type(type, &t_bool, -1, 0, cctx, FALSE, FALSE);
}
