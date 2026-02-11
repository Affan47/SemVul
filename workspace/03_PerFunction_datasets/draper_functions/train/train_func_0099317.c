show_dir_entry(const char *tag, struct dir_entry *ent)
{
	int len = prefix_len;
	int offset = prefix_offset;

	if (len >= ent->len)
		die("git-ls-files: internal error - directory entry not superset of prefix");

	if (pathspec && !match(pathspec, ps_matched, ent->name, len))
		return;

	fputs(tag, stdout);
	write_name_quoted("", 0, ent->name + offset, line_terminator, stdout);
	putchar(line_terminator);
}
