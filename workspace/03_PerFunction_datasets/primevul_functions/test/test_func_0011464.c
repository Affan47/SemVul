nv_undo(cmdarg_T *cap)
{
    if (cap->oap->op_type == OP_LOWER || VIsual_active)
    {

	cap->cmdchar = 'g';
	cap->nchar = 'u';
	nv_operator(cap);
    }
    else
	nv_kundo(cap);
}
