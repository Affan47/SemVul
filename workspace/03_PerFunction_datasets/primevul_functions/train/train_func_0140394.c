static void nsg_mrxu_parse_report(struct sony_sc *sc, u8 *rd, int size)
{
	int n, offset, relx, rely;
	u8 active;


	offset = 1;

	input_report_key(sc->touchpad, BTN_LEFT, rd[offset] & 0x0F);
	active = (rd[offset] >> 4);
	relx = (s8) rd[offset+5];
	rely = ((s8) rd[offset+10]) * -1;

	offset++;

	for (n = 0; n < 2; n++) {
		u16 x, y;
		u8 contactx, contacty;

		x = rd[offset] | ((rd[offset+1] & 0x0F) << 8);
		y = ((rd[offset+1] & 0xF0) >> 4) | (rd[offset+2] << 4);

		input_mt_slot(sc->touchpad, n);
		input_mt_report_slot_state(sc->touchpad, MT_TOOL_FINGER, active & 0x03);

		if (active & 0x03) {
			contactx = rd[offset+3] & 0x0F;
			contacty = rd[offset+3] >> 4;
			input_report_abs(sc->touchpad, ABS_MT_TOUCH_MAJOR,
				max(contactx, contacty));
			input_report_abs(sc->touchpad, ABS_MT_TOUCH_MINOR,
				min(contactx, contacty));
			input_report_abs(sc->touchpad, ABS_MT_ORIENTATION,
				(bool) (contactx > contacty));
			input_report_abs(sc->touchpad, ABS_MT_POSITION_X, x);
			input_report_abs(sc->touchpad, ABS_MT_POSITION_Y,
				NSG_MRXU_MAX_Y - y);


			if ((n == 0) || ((n == 1) && (active & 0x01))) {
				input_report_rel(sc->touchpad, REL_X, relx);
				input_report_rel(sc->touchpad, REL_Y, rely);
			}
		}

		offset += 5;
		active >>= 2;
	}

	input_mt_sync_frame(sc->touchpad);

	input_sync(sc->touchpad);
}
