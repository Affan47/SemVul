static int fdt_include_supernodes(struct fdt_region_state *info, int depth)
{
	int base = fdt_off_dt_struct(info->fdt);
	int start, stop_at;
	int i;


	for (i = 0; i <= depth; i++) {
		if (!info->stack[i].included) {
			start = info->stack[i].offset;


			fdt_next_tag(info->fdt, start, &stop_at);
			if (fdt_add_region(info, base + start, stop_at - start))
				return -1;


			info->stack[i].included = 1;
			info->can_merge = 1;
		}


		if (!info->stack[i].want)
			info->stack[i].want = WANT_NODES_ONLY;
	}

	return 0;
}
