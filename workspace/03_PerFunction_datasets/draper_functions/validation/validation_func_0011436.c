rtl8152_up(struct r8152 *tp)
{
	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return;

	r8152_aldps_en(tp, false);
	r8152b_exit_oob(tp);
	r8152_aldps_en(tp, true);
}
