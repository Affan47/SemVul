static int __init tc_filter_init(void)
{
	struct rtnetlink_link *link_p = rtnetlink_links[PF_UNSPEC];


	if (link_p) {
		link_p[RTM_NEWTFILTER-RTM_BASE].doit = tc_ctl_tfilter;
		link_p[RTM_DELTFILTER-RTM_BASE].doit = tc_ctl_tfilter;
		link_p[RTM_GETTFILTER-RTM_BASE].doit = tc_ctl_tfilter;
		link_p[RTM_GETTFILTER-RTM_BASE].dumpit = tc_dump_tfilter;
	}
	return 0;
}
