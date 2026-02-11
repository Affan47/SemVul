smp_fetch_rdp_cookie_cnt(struct proxy *px, struct session *s, void *l7, unsigned int opt,
                         const struct arg *args, struct sample *smp, const char *kw)
{
	int ret;

	ret = smp_fetch_rdp_cookie(px, s, l7, opt, args, smp, kw);

	if (smp->flags & SMP_F_MAY_CHANGE)
		return 0;

	smp->flags = SMP_F_VOLATILE;
	smp->type = SMP_T_UINT;
	smp->data.uint = ret;
	return 1;
}
