nv_home(cmdarg_T *cap)
{

    if (mod_mask & MOD_MASK_CTRL)
	nv_goto(cap);
    else
    {
	cap->count0 = 1;
	nv_pipe(cap);
    }
    ins_at_eol = FALSE;

}
