nv_open(cmdarg_T *cap)
{
#ifdef FEAT_DIFF

    if (cap->oap->op_type == OP_DELETE && cap->cmdchar == 'o')
    {
	clearop(cap->oap);
	nv_diffgetput(FALSE, cap->opcount);
    }
    else
#endif
    if (VIsual_active)
	v_swap_corners(cap->cmdchar);
#ifdef FEAT_JOB_CHANNEL
    else if (bt_prompt(curbuf))
	clearopbeep(cap->oap);
#endif
    else
	n_opencmd(cap);
}
