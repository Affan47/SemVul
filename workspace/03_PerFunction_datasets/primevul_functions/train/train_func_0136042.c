static void k_shift(struct vc_data *vc, unsigned char value, char up_flag)
{
	int old_state = shift_state;

	if (rep)
		return;


	if (value == KVAL(K_CAPSSHIFT)) {
		value = KVAL(K_SHIFT);
		if (!up_flag)
			clr_vc_kbd_led(kbd, VC_CAPSLOCK);
	}

	if (up_flag) {


		if (shift_down[value])
			shift_down[value]--;
	} else
		shift_down[value]++;

	if (shift_down[value])
		shift_state |= (1 << value);
	else
		shift_state &= ~(1 << value);


	if (up_flag && shift_state != old_state && npadch_active) {
		if (kbd->kbdmode == VC_UNICODE)
			to_utf8(vc, npadch_value);
		else
			put_queue(vc, npadch_value & 0xff);
		npadch_active = false;
	}
}
