hfsc_print_xstats(struct qdisc_util *qu, FILE *f, struct rtattr *xstats)
{
	struct tc_hfsc_stats *st;

	if (xstats == NULL)
		return 0;
	if (RTA_PAYLOAD(xstats) < sizeof(*st))
		return -1;
	st = RTA_DATA(xstats);

	fprintf(f, " period %u ", st->period);
	if (st->work != 0)
		fprintf(f, "work %llu bytes ", (unsigned long long) st->work);
	if (st->rtwork != 0)
		fprintf(f, "rtwork %llu bytes ", (unsigned long long) st->rtwork);
	fprintf(f, "level %u ", st->level);
	fprintf(f, "\n");

	return 0;
}
