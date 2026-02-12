apply_autocmds(
    event_T	event,
    char_u	*fname,
    char_u	*fname_io,
    int		force,
    buf_T	*buf)
{
    return apply_autocmds_group(event, fname, fname_io, force,
						      AUGROUP_ALL, buf, NULL);
}
