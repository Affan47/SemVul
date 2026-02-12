nv_hor_scrollbar(cmdarg_T *cap)
{
    if (cap->oap->op_type != OP_NOP)
	clearopbeep(cap->oap);


    gui_do_horiz_scroll(scrollbar_value, FALSE);
}
