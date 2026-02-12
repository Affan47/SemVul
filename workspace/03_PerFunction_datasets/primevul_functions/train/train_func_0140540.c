static void dualshock4_send_output_report(struct sony_sc *sc)
{
	struct hid_device *hdev = sc->hdev;
	u8 *buf = sc->output_report_dmabuf;
	int offset;


	if (sc->quirks & (DUALSHOCK4_CONTROLLER_USB | DUALSHOCK4_DONGLE)) {
		memset(buf, 0, DS4_OUTPUT_REPORT_0x05_SIZE);
		buf[0] = 0x05;
		buf[1] = 0x07;
		offset = 4;
	} else {
		memset(buf, 0, DS4_OUTPUT_REPORT_0x11_SIZE);
		buf[0] = 0x11;
		buf[1] = 0xC0  | sc->ds4_bt_poll_interval;
		buf[3] = 0x07;
		offset = 6;
	}

#ifdef CONFIG_SONY_FF
	buf[offset++] = sc->right;
	buf[offset++] = sc->left;
#else
	offset += 2;
#endif


	if (sc->led_state[3]) {
		buf[offset++] = sc->led_state[0];
		buf[offset++] = sc->led_state[1];
		buf[offset++] = sc->led_state[2];
	} else {
		offset += 3;
	}


	buf[offset++] = sc->led_delay_on[3];
	buf[offset++] = sc->led_delay_off[3];

	if (sc->quirks & (DUALSHOCK4_CONTROLLER_USB | DUALSHOCK4_DONGLE))
		hid_hw_output_report(hdev, buf, DS4_OUTPUT_REPORT_0x05_SIZE);
	else {

		u8 bthdr = 0xA2;
		u32 crc;

		crc = crc32_le(0xFFFFFFFF, &bthdr, 1);
		crc = ~crc32_le(crc, buf, DS4_OUTPUT_REPORT_0x11_SIZE-4);
		put_unaligned_le32(crc, &buf[74]);
		hid_hw_output_report(hdev, buf, DS4_OUTPUT_REPORT_0x11_SIZE);
	}
}
