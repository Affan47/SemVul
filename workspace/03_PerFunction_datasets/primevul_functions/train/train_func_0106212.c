static int commit_match(struct commit *commit, struct rev_info *opt)
{
	if (!opt->grep_filter)
		return 1;
	return grep_buffer(opt->grep_filter,
			   NULL,
			   commit->buffer, strlen(commit->buffer));
}
