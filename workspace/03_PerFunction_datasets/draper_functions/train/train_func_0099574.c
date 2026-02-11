dccp_parse(struct xt_option_call *cb)
{
	struct xt_dccp_info *einfo = cb->data;

	xtables_option_parse(cb);
	switch (cb->entry->id) {
	case O_SOURCE_PORT:
		einfo->flags |= XT_DCCP_SRC_PORTS;
		if (cb->invert)
			einfo->invflags |= XT_DCCP_SRC_PORTS;
		break;
	case O_DEST_PORT:
		einfo->flags |= XT_DCCP_DEST_PORTS;
		if (cb->invert)
			einfo->invflags |= XT_DCCP_DEST_PORTS;
		break;
	case O_DCCP_TYPES:
		einfo->flags |= XT_DCCP_TYPE;
		einfo->typemask = parse_dccp_types(cb->arg);
		if (cb->invert)
			einfo->invflags |= XT_DCCP_TYPE;
		break;
	case O_DCCP_OPTION:
		einfo->flags |= XT_DCCP_OPTION;
		if (cb->invert)
			einfo->invflags |= XT_DCCP_OPTION;
		break;
	}
}
