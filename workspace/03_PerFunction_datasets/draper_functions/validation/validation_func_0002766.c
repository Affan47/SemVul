cmd_show(int argc, const char **argv, const char *prefix)
{
	struct rev_info rev;
	struct object_array_entry *objects;
	int i, count, ret = 0;

	git_config(git_log_config, NULL);

	if (diff_use_color_default == -1)
		diff_use_color_default = git_use_color_default;

	init_revisions(&rev, prefix);
	rev.diff = 1;
	rev.combine_merges = 1;
	rev.dense_combined_merges = 1;
	rev.always_show_header = 1;
	rev.ignore_merges = 0;
	rev.no_walk = 1;
	cmd_log_init(argc, argv, prefix, &rev);

	count = rev.pending.nr;
	objects = rev.pending.objects;
	for (i = 0; i < count && !ret; i++) {
		struct object *o = objects[i].item;
		const char *name = objects[i].name;
		switch (o->type) {
		case OBJ_BLOB:
			ret = show_object(o->sha1, 0, NULL);
			break;
		case OBJ_TAG: {
			struct tag *t = (struct tag *)o;

			printf("%stag %s%s\n",
					diff_get_color_opt(&rev.diffopt, DIFF_COMMIT),
					t->tag,
					diff_get_color_opt(&rev.diffopt, DIFF_RESET));
			ret = show_object(o->sha1, 1, &rev);
			objects[i].item = parse_object(t->tagged->sha1);
			i--;
			break;
		}
		case OBJ_TREE:
			printf("%stree %s%s\n\n",
					diff_get_color_opt(&rev.diffopt, DIFF_COMMIT),
					name,
					diff_get_color_opt(&rev.diffopt, DIFF_RESET));
			read_tree_recursive((struct tree *)o, "", 0, 0, NULL,
					show_tree_object, NULL);
			break;
		case OBJ_COMMIT:
			rev.pending.nr = rev.pending.alloc = 0;
			rev.pending.objects = NULL;
			add_object_array(o, name, &rev.pending);
			ret = cmd_log_walk(&rev);
			break;
		default:
			ret = error("Unknown type: %d", o->type);
		}
	}
	free(objects);
	return ret;
}
