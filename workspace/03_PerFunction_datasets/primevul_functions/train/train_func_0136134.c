void check_format_options(void)
{
	if (!format) {

		if (DISPLAY_HDR_ONLY(flags)) {
			format = F_HEADER_OUTPUT;
		}
		else {
			format = F_PPC_OUTPUT;
		}
	}


	f_position = get_format_position(format);


	if (!ACCEPT_HEADER_ONLY(fmt[f_position]->options)) {

		flags &= ~S_F_HDR_ONLY;
	}
	if (!ACCEPT_HORIZONTALLY(fmt[f_position]->options)) {

		flags &= ~S_F_HORIZONTALLY;
	}
	if (!ACCEPT_LOCAL_TIME(fmt[f_position]->options)) {

		flags &= ~(S_F_LOCAL_TIME + S_F_TRUE_TIME);
	}
	if (!ACCEPT_SEC_EPOCH(fmt[f_position]->options)) {

		flags &= ~S_F_SEC_EPOCH;
	}
	if (REJECT_TRUE_TIME(fmt[f_position]->options)) {

		flags &= ~S_F_TRUE_TIME;
	}
}
