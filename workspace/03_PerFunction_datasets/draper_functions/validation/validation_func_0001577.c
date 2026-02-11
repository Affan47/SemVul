wt_status_print(struct wt_status *s)
{
	unsigned char sha1[20];
	s->is_initial = get_sha1(s->reference, sha1) ? 1 : 0;

	if (s->branch) {
		const char *on_what = "On branch ";
		const char *branch_name = s->branch;
		if (!prefixcmp(branch_name, "refs/heads/"))
			branch_name += 11;
		else if (!strcmp(branch_name, "HEAD")) {
			branch_name = "";
			on_what = "Not currently on any branch.";
		}
		color_printf_ln(color(WT_STATUS_HEADER),
			"# %s%s", on_what, branch_name);
	}

	if (s->is_initial) {
		color_printf_ln(color(WT_STATUS_HEADER), "#");
		color_printf_ln(color(WT_STATUS_HEADER), "# Initial commit");
		color_printf_ln(color(WT_STATUS_HEADER), "#");
		wt_status_print_initial(s);
	}
	else {
		wt_status_print_updated(s);
	}

	wt_status_print_changed(s);
	wt_status_print_untracked(s);

	if (s->verbose && !s->is_initial)
		wt_status_print_verbose(s);
	if (!s->commitable) {
		if (s->amend)
			printf("# No changes\n");
		else if (s->workdir_dirty)
			printf("no changes added to commit (use \"git add\" and/or \"git commit -a\")\n");
		else if (s->workdir_untracked)
			printf("nothing added to commit but untracked files present (use \"git add\" to track)\n");
		else if (s->is_initial)
			printf("nothing to commit (create/copy files and use \"git add\" to track)\n");
		else
			printf("nothing to commit (working directory clean)\n");
	}
}
