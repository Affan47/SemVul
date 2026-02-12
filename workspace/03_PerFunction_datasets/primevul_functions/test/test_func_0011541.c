nv_end(cmdarg_T *cap)
{
    if (cap->arg || (mod_mask & MOD_MASK_CTRL))
    {
	cap->arg = TRUE;
	nv_goto(cap);
	cap->count1 = 1;
    }
    nv_dollar(cap);
}
