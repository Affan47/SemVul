dccp_save(const void *ip, const struct xt_entry_match *match)
{
	const struct xt_dccp_info *einfo =
		(const struct xt_dccp_info *)match->data;

	if (einfo->flags & XT_DCCP_SRC_PORTS) {
		if (einfo->invflags & XT_DCCP_SRC_PORTS)
			printf(" !");
		if (einfo->spts[0] != einfo->spts[1])
			printf(" --sport %u:%u",
			       einfo->spts[0], einfo->spts[1]);
		else
			printf(" --sport %u", einfo->spts[0]);
	}

	if (einfo->flags & XT_DCCP_DEST_PORTS) {
		if (einfo->invflags & XT_DCCP_DEST_PORTS)
			printf(" !");
		if (einfo->dpts[0] != einfo->dpts[1])
			printf(" --dport %u:%u",
			       einfo->dpts[0], einfo->dpts[1]);
		else
			printf(" --dport %u", einfo->dpts[0]);
	}

	if (einfo->flags & XT_DCCP_TYPE) {
		printf("%s --dccp-types",
		       einfo->invflags & XT_DCCP_TYPE ? " !" : "");
		print_types(einfo->typemask, false, 0);
	}

	if (einfo->flags & XT_DCCP_OPTION) {
		printf("%s --dccp-option %u",
			einfo->invflags & XT_DCCP_OPTION ? " !" : "",
			einfo->option);
	}
}
