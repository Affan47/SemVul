do_source(
    char_u	*fname,
    int		check_other,
    int		is_vimrc,
    int		*ret_sid UNUSED)
{
    return do_source_ext(fname, check_other, is_vimrc, ret_sid, NULL, FALSE);
}
