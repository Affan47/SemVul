print_devgroup(unsigned int id, unsigned int mask, int numeric)
{
	const char *name = NULL;

	if (mask != 0xffffffff)
		printf("0x%x/0x%x", id, mask);
	else {
		if (numeric == 0)
			name = xtables_lmap_id2name(devgroups, id);
		if (name)
			printf("%s", name);
		else
			printf("0x%x", id);
	}
}
