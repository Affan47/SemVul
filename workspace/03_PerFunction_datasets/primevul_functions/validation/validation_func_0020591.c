get_augroup_name(expand_T *xp UNUSED, int idx)
{
    if (idx == augroups.ga_len)
	return (char_u *)"END";
    if (idx >= augroups.ga_len)
	return NULL;
    if (AUGROUP_NAME(idx) == NULL || AUGROUP_NAME(idx) == get_deleted_augroup())

	return (char_u *)"";
    return AUGROUP_NAME(idx);
}
