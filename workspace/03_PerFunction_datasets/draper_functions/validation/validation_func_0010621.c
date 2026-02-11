cmd_prune(int argc, const char **argv, const char *prefix)
{
	struct rev_info revs;
	const struct option options[] = {
		OPT_BOOLEAN('n', NULL, &show_only,
			    "do not remove, show only"),
		OPT_BOOLEAN('v', NULL, &verbose,
			"report pruned objects"),
		OPT_DATE(0, "expire", &expire,
			 "expire objects older than <time>"),
		OPT_END()
	};
	char *s;

	save_commit_buffer = 0;
	init_revisions(&revs, prefix);

	argc = parse_options(argc, argv, options, prune_usage, 0);
	while (argc--) {
		unsigned char sha1[20];
		const char *name = *argv++;

		if (!get_sha1(name, sha1)) {
			struct object *object = parse_object(sha1);
			if (!object)
				die("bad object: %s", name);
			add_pending_object(&revs, object, "");
		}
		else
			die("unrecognized argument: %s", name);
	}
	mark_reachable_objects(&revs, 1);
	prune_object_dir(get_object_directory());

	prune_packed_objects(show_only);
	remove_temporary_files(get_object_directory());
	s = xstrdup(mkpath("%s/pack", get_object_directory()));
	remove_temporary_files(s);
	free(s);
	return 0;
}
