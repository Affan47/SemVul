encapinfo_write(char *outfile, encapinfo_t *pkginfo)
{
	FILE *f;
	struct linkname *lnp;
	encap_hashptr_t hp;
	encap_listptr_t lp;

#ifdef DEBUG
	printf("==> encapinfo_write(\"%s\", 0x%lx)\n", outfile, pkginfo);
#endif

	encap_listptr_reset(&lp);

	f = fopen(outfile, "w");
	if (f == NULL)
		return -1;

	fprintf(f, "encap %s\t# libencap-%s\n",
		pkginfo->ei_pkgfmt, libencap_version);

	if (pkginfo->ei_platform != NULL)
		fprintf(f, "platform %s\n", pkginfo->ei_platform);

#ifdef ENCAPINFO_DATE_TIME_T
	if (pkginfo->ei_date != 0)
	{
		char buf[1024];

		strftime(buf, 1024, "%a %b %d %H:%M:%S %Z %Y",
			 localtime(&pkginfo->ei_date));

		fprintf(f, "date %s\n", buf);
	}
#else
	if (pkginfo->ei_date != NULL)
		fprintf(f, "date %s\n", pkginfo->ei_date);
#endif

	if (pkginfo->ei_contact != NULL)
		fprintf(f, "contact %s\n", pkginfo->ei_contact);

	if (pkginfo->ei_description != NULL)
		fprintf(f, "description %s\n", pkginfo->ei_description);

	if (pkginfo->ei_ex_l != NULL)
	{
		encap_listptr_reset(&lp);
		while (encap_list_next(pkginfo->ei_ex_l, &lp))
			fprintf(f, "exclude %s\n",
				(char *)encap_listptr_data(&lp));
	}

	if (pkginfo->ei_rl_l != NULL)
	{
		encap_listptr_reset(&lp);
		while (encap_list_next(pkginfo->ei_rl_l, &lp))
			fprintf(f, "require %s\n",
				(char *)encap_listptr_data(&lp));
	}

	if (pkginfo->ei_ld_l != NULL)
	{
		encap_listptr_reset(&lp);
		while (encap_list_next(pkginfo->ei_ld_l, &lp))
			fprintf(f, "linkdir %s\n",
				(char *)encap_listptr_data(&lp));
	}

	if (pkginfo->ei_pr_l != NULL)
	{
		encap_listptr_reset(&lp);
		while (encap_list_next(pkginfo->ei_pr_l, &lp))
		{
			char buf[MAXPATHLEN];
			ENCAP_PREREQ *epp;

			epp = (ENCAP_PREREQ *)encap_listptr_data(&lp);

			encap_prereq_print(epp, buf, sizeof(buf));
			fprintf(f, "prereq %s\n", buf);
		}
	}

	if (pkginfo->ei_ln_h != NULL)
	{
		encap_hashptr_reset(&hp);
		while (encap_hash_next(pkginfo->ei_ln_h, &hp))
		{
			lnp = (linkname_t *)encap_hashptr_data(&hp);
			fprintf(f, "linkname %s %s\n", lnp->ln_pkgdir_path,
				lnp->ln_newname);
		}
	}

	fclose(f);
	return 0;
}
