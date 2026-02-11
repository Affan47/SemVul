squash_message(void)
{
	struct rev_info rev;
	struct commit *commit;
	struct strbuf out = STRBUF_INIT;
	struct commit_list *j;
	int fd;

	printf("Squash commit -- not updating HEAD\n");
	fd = open(git_path("SQUASH_MSG"), O_WRONLY | O_CREAT, 0666);
	if (fd < 0)
		die("Could not write to %s", git_path("SQUASH_MSG"));

	init_revisions(&rev, NULL);
	rev.ignore_merges = 1;
	rev.commit_format = CMIT_FMT_MEDIUM;

	commit = lookup_commit(head);
	commit->object.flags |= UNINTERESTING;
	add_pending_object(&rev, &commit->object, NULL);

	for (j = remoteheads; j; j = j->next)
		add_pending_object(&rev, &j->item->object, NULL);

	setup_revisions(0, NULL, &rev, NULL);
	if (prepare_revision_walk(&rev))
		die("revision walk setup failed");

	strbuf_addstr(&out, "Squashed commit of the following:\n");
	while ((commit = get_revision(&rev)) != NULL) {
		strbuf_addch(&out, '\n');
		strbuf_addf(&out, "commit %s\n",
			sha1_to_hex(commit->object.sha1));
		pretty_print_commit(rev.commit_format, commit, &out, rev.abbrev,
			NULL, NULL, rev.date_mode, 0);
	}
	write(fd, out.buf, out.len);
	close(fd);
	strbuf_release(&out);
}
