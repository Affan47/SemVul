PreviousWord_action(Widget w _is_unused, XEvent *event, String *params,
    Cardinal *num_params)
{
	register int baddr;
	int baddr0;
	unsigned char  c;
	Boolean prot;

	action_debug(PreviousWord_action, event, params, num_params);
	reset_idle_timer();
	if (kybdlock) {
		enq_ta(PreviousWord_action, CN, CN);
		return;
	}
#if defined(X3270_ANSI)
	if (IN_ANSI)
		return;
#endif
	if (!formatted)
		return;

	baddr = cursor_addr;
	prot = FA_IS_PROTECTED(get_field_attribute(baddr));


	if (!prot) {
		c = ea_buf[baddr].cc;
		while (!ea_buf[baddr].fa && c != EBC_space && c != EBC_null) {
			DEC_BA(baddr);
			if (baddr == cursor_addr)
				return;
			c = ea_buf[baddr].cc;
		}
	}
	baddr0 = baddr;


	do {
		c = ea_buf[baddr].cc;
		if (ea_buf[baddr].fa) {
			DEC_BA(baddr);
			prot = FA_IS_PROTECTED(get_field_attribute(baddr));
			continue;
		}
		if (!prot && c != EBC_space && c != EBC_null)
			break;
		DEC_BA(baddr);
	} while (baddr != baddr0);

	if (baddr == baddr0)
		return;


	for (;;) {
		DEC_BA(baddr);
		c = ea_buf[baddr].cc;
		if (ea_buf[baddr].fa || c == EBC_space || c == EBC_null) {
			break;
		}
	}
	INC_BA(baddr);
	cursor_move(baddr);
}
