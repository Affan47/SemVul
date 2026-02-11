xen_hyper_cmd_domain(void)
{
	struct xen_hyper_cmd_args da;
	struct xen_hyper_domain_context *dc;
	ulong val;
        int c, cnt, type, bogus;

	BZERO(&da, sizeof(struct xen_hyper_cmd_args));
        while ((c = getopt(argcnt, args, "")) != EOF) {
                switch(c)
                {
                default:
                        argerrs++;
                        break;
                }
        }

        if (argerrs)
                cmd_usage(pc->curcmd, SYNOPSIS);

	cnt = bogus = 0;
        while (args[optind]) {
		if (IS_A_NUMBER(args[optind])) {
			type = xen_hyper_str_to_domain_context(args[optind], &val, &dc);
			switch (type) {
			case XEN_HYPER_STR_DID:
			case XEN_HYPER_STR_DOMAIN:
				da.value[cnt] = val;
				da.type[cnt] = type;
				da.addr[cnt] = dc->domain;
				da.context[cnt] = dc;
				cnt++;
				break;
			case XEN_HYPER_STR_INVALID:
				error(INFO, "invalid domain or id value: %s\n\n",
					args[optind]);
				bogus++;
			}
		} else {
			error(FATAL, "invalid address: %s\n",
				args[optind]);
		}
		optind++;
	}
	da.cnt = cnt;
	if (bogus && !cnt) {
		return;
	}

	xen_hyper_do_domain(&da);
}
