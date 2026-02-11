connbytes_save(const void *ip, const struct xt_entry_match *match)
{
	const struct xt_connbytes_info *sinfo = (const void *)match->data;

	if (sinfo->count.from > sinfo->count.to)
		printf(" ! --connbytes %llu:%llu",
			(unsigned long long)sinfo->count.to,
			(unsigned long long)sinfo->count.from);
	else
		printf(" --connbytes %llu:%llu",
			(unsigned long long)sinfo->count.from,
			(unsigned long long)sinfo->count.to);

	fputs(" --connbytes-mode", stdout);
	print_mode(sinfo);

	fputs(" --connbytes-dir", stdout);
	print_direction(sinfo);
}
