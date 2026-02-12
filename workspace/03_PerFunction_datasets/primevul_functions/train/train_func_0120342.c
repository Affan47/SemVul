set_sys_leap(u_char new_sys_leap) {
	sys_leap = new_sys_leap;
	xmt_leap = sys_leap;


	if (xmt_leap != LEAP_NOTINSYNC) {
		if (leap_sec_in_progress) {

			xmt_leap = LEAP_NOTINSYNC;
		}
#ifdef LEAP_SMEAR
		else {


			if (leap_smear.enabled)
				xmt_leap = LEAP_NOWARNING;
		}
#endif
	}
}
