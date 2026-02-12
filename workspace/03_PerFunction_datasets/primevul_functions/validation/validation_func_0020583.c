write_lnum_adjust(linenr_T offset)
{
    if (curbuf->b_no_eol_lnum != 0)
	curbuf->b_no_eol_lnum += offset;
}
