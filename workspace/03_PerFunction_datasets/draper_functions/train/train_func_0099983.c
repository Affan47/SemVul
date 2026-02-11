nv_mark(cap)
    cmdarg_T	*cap;
{
    if (!checkclearop(cap->oap))
    {
	if (setmark(cap->nchar) == FAIL)
	    clearopbeep(cap->oap);
    }
}
