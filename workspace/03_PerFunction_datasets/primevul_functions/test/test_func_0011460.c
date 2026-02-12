nv_ctrlh(cmdarg_T *cap)
{
    if (VIsual_active && VIsual_select)
    {
	cap->cmdchar = 'x';
	v_visop(cap);
    }
    else
	nv_left(cap);
}
