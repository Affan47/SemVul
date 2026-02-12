nv_Undo(cmdarg_T *cap)
{

    if (cap->oap->op_type == OP_UPPER || VIsual_active)
    {

	cap->cmdchar = 'g';
	cap->nchar = 'U';
	nv_operator(cap);
    }
    else if (!checkclearopq(cap->oap))
    {
	u_undoline();
	curwin->w_set_curswant = TRUE;
    }
}
