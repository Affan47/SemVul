set_target_parse_v1(int c, char **argv, int invert, unsigned int *flags,
		    const void *entry, struct xt_entry_target **target)
{
	struct xt_set_info_target_v1 *myinfo =
		(struct xt_set_info_target_v1 *) (*target)->data;

	switch (c) {
	case '1':
		parse_target(argv, invert, &myinfo->add_set, "add-set");
		*flags |= SET_TARGET_ADD;
		break;
	case '2':
		parse_target(argv, invert, &myinfo->del_set, "del-set");
		*flags |= SET_TARGET_DEL;
		break;
	}
	return 1;
}
