nv_dot(cmdarg_T *cap)
{
    if (!checkclearopq(cap->oap))
    {


	if (start_redo(cap->count0, restart_edit != 0 && !arrow_used) == FAIL)
	    clearopbeep(cap->oap);
    }
}
