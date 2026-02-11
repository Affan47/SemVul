get_patch_ids(struct rev_info *rev, struct patch_ids *ids, const char *prefix)
{
	struct rev_info check_rev;
	struct commit *commit;
	struct object *o1, *o2;
	unsigned flags1, flags2;

	if (rev->pending.nr != 2)
		die("Need exactly one range.");

	o1 = rev->pending.objects[0].item;
	flags1 = o1->flags;
	o2 = rev->pending.objects[1].item;
	flags2 = o2->flags;

	if ((flags1 & UNINTERESTING) == (flags2 & UNINTERESTING))
		die("Not a range.");

	init_patch_ids(ids);


	init_revisions(&check_rev, prefix);
	o1->flags ^= UNINTERESTING;
	o2->flags ^= UNINTERESTING;
	add_pending_object(&check_rev, o1, "o1");
	add_pending_object(&check_rev, o2, "o2");
	prepare_revision_walk(&check_rev);

	while ((commit = get_revision(&check_rev)) != NULL) {

		if (commit->parents && commit->parents->next)
			continue;

		add_commit_patch_id(commit, ids);
	}


	clear_commit_marks((struct commit *)o1,
			SEEN | UNINTERESTING | SHOWN | ADDED);
	clear_commit_marks((struct commit *)o2,
			SEEN | UNINTERESTING | SHOWN | ADDED);
	o1->flags = flags1;
	o2->flags = flags2;
}
