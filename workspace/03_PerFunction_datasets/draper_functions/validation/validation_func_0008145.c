get_object_list(int ac, const char **av)
{
	struct rev_info revs;
	char line[1000];
	int flags = 0;

	init_revisions(&revs, NULL);
	save_commit_buffer = 0;
	track_object_refs = 0;
	setup_revisions(ac, av, &revs, NULL);

	while (fgets(line, sizeof(line), stdin) != NULL) {
		int len = strlen(line);
		if (line[len - 1] == '\n')
			line[--len] = 0;
		if (!len)
			break;
		if (*line == '-') {
			if (!strcmp(line, "--not")) {
				flags ^= UNINTERESTING;
				continue;
			}
			die("not a rev '%s'", line);
		}
		if (handle_revision_arg(line, &revs, flags, 1))
			die("bad revision '%s'", line);
	}

	prepare_revision_walk(&revs);
	mark_edges_uninteresting(revs.commits, &revs, show_edge);
	traverse_commit_list(&revs, show_commit, show_object);
}
