static int check_ref(const char *name, unsigned int flags)
{
	if (!flags)
		return 1;

	if (!skip_prefix(name, "refs/", &name))
		return 0;


	if ((flags & REF_NORMAL) && check_refname_format(name, 0))
		return 0;


	if ((flags & REF_HEADS) && starts_with(name, "heads/"))
		return 1;


	if ((flags & REF_TAGS) && starts_with(name, "tags/"))
		return 1;


	return !(flags & ~REF_NORMAL);
}
