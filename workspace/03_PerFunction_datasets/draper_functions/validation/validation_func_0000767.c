devgroup_parse(int c, char **argv, int invert, unsigned int *flags,
                       const void *entry, struct xt_entry_match **match)
{
	struct xt_devgroup_info *info = (struct xt_devgroup_info *)(*match)->data;
	unsigned int id;
	char *end;

	switch (c) {
	case XT_DEVGROUP_OPT_SRCGROUP:
		xtables_check_inverse(optarg, &invert, &optind, 0, argv);
		end = optarg;
		info->src_group = strtoul(optarg, &end, 0);
		if (end != optarg && (*end == '/' || *end == '\0')) {
			if (*end == '/')
				info->src_mask = strtoul(end+1, &end, 0);
			else
				info->src_mask = 0xffffffff;
			if (*end != '\0' || end == optarg)
				xtables_error(PARAMETER_PROBLEM,
					      "Bad src-group value `%s'",
					      optarg);
		} else {
			id = devgroup_name2id(optarg);
			if (id == -1)
				xtables_error(PARAMETER_PROBLEM,
					      "Device group `%s' not found",
					      optarg);
			info->src_group = id;
			info->src_mask  = 0xffffffff;
		}
		info->flags |= XT_DEVGROUP_MATCH_SRC;
		if (invert)
			info->flags |= XT_DEVGROUP_INVERT_SRC;
		*flags |= c;
		break;
	case XT_DEVGROUP_OPT_DSTGROUP:
		xtables_check_inverse(optarg, &invert, &optind, 0, argv);
		end = optarg;
		info->dst_group = strtoul(optarg, &end, 0);
		if (end != optarg && (*end == '/' || *end == '\0')) {
			if (*end == '/')
				info->dst_mask = strtoul(end+1, &end, 0);
			else
				info->dst_mask = 0xffffffff;
			if (*end != '\0' || end == optarg)
				xtables_error(PARAMETER_PROBLEM,
					      "Bad dst-group value `%s'",
					      optarg);
		} else {
			id = devgroup_name2id(optarg);
			if (id == -1)
				xtables_error(PARAMETER_PROBLEM,
					      "Device group `%s' not found",
					      optarg);
			info->dst_group = id;
			info->dst_mask  = 0xffffffff;
		}
		info->flags |= XT_DEVGROUP_MATCH_DST;
		if (invert)
			info->flags |= XT_DEVGROUP_INVERT_DST;
		*flags |= c;
		break;
	}
	return 1;
}
