insert_pkg_in_hash(char *pkgspec, encap_hash_t *h)
{
	char name[MAXPATHLEN], ver[MAXPATHLEN];
	encap_hashptr_t hp;
	package_versions_t pvs, *pvp;

#ifdef DEBUG
	printf("==> insert_pkg_in_hash(pkgspec=\"%s\", h=0x%lx)\n", pkgspec, h);
#endif

	encap_pkgspec_parse(pkgspec, name, sizeof(name), ver, sizeof(ver),
			    NULL, 0, NULL, 0);
	if (name == NULL || ver == NULL)
	{
		fprintf(stderr, "    ! error parsing pkgspec\n");
		return -1;
	}

	strlcpy(pvs.pv_pkgname, name, sizeof(pvs.pv_pkgname));
	pvs.pv_ver_l = NULL;
	encap_hashptr_reset(&hp);
	if (encap_hash_getkey(h, &hp, &pvs, NULL) != 0)
	{
		pvp = (package_versions_t *)encap_hashptr_data(&hp);
#ifdef DEBUG
		printf("    insert_pkg_in_hash(): found entry for package %s\n",
		       name);
		printf("    insert_pkg_in_hash(): hp.bucket = %d\n",
		       hp.bucket);
#endif
	}
	else
	{
		pvs.pv_ver_l = encap_list_new(LIST_USERFUNC,
					   (encap_cmpfunc_t)encap_vercmp);
		if (pvs.pv_ver_l == NULL)
		{
			fprintf(stderr,
				"    ! malloc() failed in encap_list_new()\n");
			return -1;
		}
		pvp = (package_versions_t *)malloc(sizeof(package_versions_t));
		memcpy(pvp, &pvs, sizeof(package_versions_t));
		if (encap_hash_add(h, pvp) != 0)
		{
			fprintf(stderr,
				"    ! encap_hash_insert() failed!\n");
			return -1;
		}
	}


	if (encap_list_add(pvp->pv_ver_l, strdup(ver)) != 0)
	{
		fprintf(stderr, "    ! encap_list_add() failed!\n");
		return -1;
	}

	return 0;
}
