list_tags(const char *pattern, int lines)
{
	struct tag_filter filter;

	if (pattern == NULL)
		pattern = "*";

	filter.pattern = pattern;
	filter.lines = lines;

	for_each_tag_ref(show_reference, (void *) &filter);

	return 0;
}
