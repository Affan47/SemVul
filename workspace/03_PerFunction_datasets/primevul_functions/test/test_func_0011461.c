nv_tabline(cmdarg_T *cap)
{
    if (cap->oap->op_type != OP_NOP)
	clearopbeep(cap->oap);


    goto_tabpage(current_tab);
}
