modname(
    char_u *fname,
    char_u *ext,
    int	    prepend_dot)
{
    return buf_modname((curbuf->b_p_sn || curbuf->b_shortname),
						     fname, ext, prepend_dot);
}
