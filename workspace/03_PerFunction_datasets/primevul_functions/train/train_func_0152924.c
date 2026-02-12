op_formatexpr(oparg_T *oap)
{
    if (oap->is_VIsual)

	redraw_curbuf_later(INVERTED);

    if (fex_format(oap->start.lnum, oap->line_count, NUL) != 0)


	op_format(oap, FALSE);
}
