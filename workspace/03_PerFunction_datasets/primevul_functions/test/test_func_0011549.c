nv_window(cmdarg_T *cap)
{
    if (cap->nchar == ':')
    {

	cap->cmdchar = ':';
	cap->nchar = NUL;
	nv_colon(cap);
    }
    else if (!checkclearop(cap->oap))
	do_window(cap->nchar, cap->count0, NUL);
}
