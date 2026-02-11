builtin_diff_tree(struct rev_info *revs,
			     int argc, const char **argv,
			     struct object_array_entry *ent)
{
	const unsigned char *(sha1[2]);
	int swap = 0;

	if (argc > 1)
		usage(builtin_diff_usage);


	if (ent[1].item->flags & UNINTERESTING)
		swap = 1;
	sha1[swap] = ent[0].item->sha1;
	sha1[1-swap] = ent[1].item->sha1;
	diff_tree_sha1(sha1[0], sha1[1], "", &revs->diffopt);
	log_tree_diff_flush(revs);
	return 0;
}
