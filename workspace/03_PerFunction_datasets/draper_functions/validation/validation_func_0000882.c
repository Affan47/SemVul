xen_hyper_cmd_pcpus(void)
{
	struct xen_hyper_cmd_args pca;
	struct xen_hyper_pcpu_context *pcc;
	ulong flag;
	ulong val;
        int c, cnt, type, bogus;

	BZERO(&pca, sizeof(struct xen_hyper_cmd_args));
	flag= 0;
        while ((c = getopt(argcnt, args, "rt")) != EOF) {
                switch(c)
                {
		case 'r':
			flag |= XEN_HYPER_PCPUS_REGS;
			break;
		case 't':
			flag |= XEN_HYPER_PCPUS_TSS;
			break;
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
			type = xen_hyper_str_to_pcpu_context(args[optind], &val, &pcc);
			switch (type) {
			case XEN_HYPER_STR_PCID:
			case XEN_HYPER_STR_PCPU:
				pca.value[cnt] = val;
				pca.type[cnt] = type;
				pca.addr[cnt] = pcc->pcpu;
				pca.context[cnt] = pcc;
				cnt++;
				break;
			case XEN_HYPER_STR_INVALID:
				error(INFO, "invalid pcpu or id value: %s\n\n",
					args[optind]);
				bogus++;
			}
		} else {
			error(FATAL, "invalid address: %s\n",
				args[optind]);
		}
		optind++;
	}
	pca.cnt = cnt;
	if (bogus && !cnt) {
		return;
	}

	xen_hyper_do_pcpus(flag, &pca);
}
