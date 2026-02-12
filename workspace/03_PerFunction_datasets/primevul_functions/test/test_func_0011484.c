nv_abbrev(cmdarg_T *cap)
{
    if (cap->cmdchar == K_DEL || cap->cmdchar == K_KDEL)
	cap->cmdchar = 'x';


    if (VIsual_active)
	v_visop(cap);
    else
	nv_optrans(cap);
}
