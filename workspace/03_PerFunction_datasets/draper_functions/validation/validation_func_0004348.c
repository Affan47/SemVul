showdirs(struct dnode **dn, int first)
{
	unsigned nfiles;
	unsigned dndirs;
	struct dnode **subdnp;
	struct dnode **dnd;


	for (; *dn; dn++) {
		if (all_fmt & (DISP_DIRNAME | DISP_RECURSIVE)) {
			if (!first)
				bb_putchar('\n');
			first = 0;
			printf("%s:\n", (*dn)->fullname);
		}
		subdnp = list_dir((*dn)->fullname, &nfiles);
#if ENABLE_DESKTOP
		if ((all_fmt & STYLE_MASK) == STYLE_LONG)
			printf("total %"OFF_FMT"u\n", calculate_blocks(subdnp));
#endif
		if (nfiles > 0) {

			dnsort(subdnp, nfiles);
			showfiles(subdnp, nfiles);
			if (ENABLE_FEATURE_LS_RECURSIVE
			 && (all_fmt & DISP_RECURSIVE)
			) {

				dnd = splitdnarray(subdnp, SPLIT_SUBDIR);
				dndirs = count_dirs(subdnp, SPLIT_SUBDIR);
				if (dndirs > 0) {
					dnsort(dnd, dndirs);
					showdirs(dnd, 0);

					free(dnd);
				}
			}

			dfree(subdnp);
		}
	}
}
