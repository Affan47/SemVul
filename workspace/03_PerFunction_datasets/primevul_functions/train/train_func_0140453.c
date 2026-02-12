static int sony_raw_event(struct hid_device *hdev, struct hid_report *report,
		u8 *rd, int size)
{
	struct sony_sc *sc = hid_get_drvdata(hdev);


	if ((sc->quirks & SIXAXIS_CONTROLLER) && rd[0] == 0x01 && size == 49) {


		if (rd[1] == 0xff)
			return -EINVAL;

		swap(rd[41], rd[42]);
		swap(rd[43], rd[44]);
		swap(rd[45], rd[46]);
		swap(rd[47], rd[48]);

		sixaxis_parse_report(sc, rd, size);
	} else if ((sc->quirks & MOTION_CONTROLLER_BT) && rd[0] == 0x01 && size == 49) {
		sixaxis_parse_report(sc, rd, size);
	} else if ((sc->quirks & NAVIGATION_CONTROLLER) && rd[0] == 0x01 &&
			size == 49) {
		sixaxis_parse_report(sc, rd, size);
	} else if ((sc->quirks & DUALSHOCK4_CONTROLLER_USB) && rd[0] == 0x01 &&
			size == 64) {
		dualshock4_parse_report(sc, rd, size);
	} else if (((sc->quirks & DUALSHOCK4_CONTROLLER_BT) && rd[0] == 0x11 &&
			size == 78)) {

		u8 bthdr = 0xA1;
		u32 crc;
		u32 report_crc;

		crc = crc32_le(0xFFFFFFFF, &bthdr, 1);
		crc = ~crc32_le(crc, rd, DS4_INPUT_REPORT_0x11_SIZE-4);
		report_crc = get_unaligned_le32(&rd[DS4_INPUT_REPORT_0x11_SIZE-4]);
		if (crc != report_crc) {
			hid_dbg(sc->hdev, "DualShock 4 input report's CRC check failed, received crc 0x%0x != 0x%0x\n",
				report_crc, crc);
			return -EILSEQ;
		}

		dualshock4_parse_report(sc, rd, size);
	} else if ((sc->quirks & DUALSHOCK4_DONGLE) && rd[0] == 0x01 &&
			size == 64) {
		unsigned long flags;
		enum ds4_dongle_state dongle_state;


		bool connected = (rd[31] & 0x04) ? false : true;

		spin_lock_irqsave(&sc->lock, flags);
		dongle_state = sc->ds4_dongle_state;
		spin_unlock_irqrestore(&sc->lock, flags);


		if (dongle_state == DONGLE_DISCONNECTED && connected) {
			hid_info(sc->hdev, "DualShock 4 USB dongle: controller connected\n");
			sony_set_leds(sc);

			spin_lock_irqsave(&sc->lock, flags);
			sc->ds4_dongle_state = DONGLE_CALIBRATING;
			spin_unlock_irqrestore(&sc->lock, flags);

			sony_schedule_work(sc, SONY_WORKER_HOTPLUG);


			return 0;
		} else if ((dongle_state == DONGLE_CONNECTED ||
			    dongle_state == DONGLE_DISABLED) && !connected) {
			hid_info(sc->hdev, "DualShock 4 USB dongle: controller disconnected\n");

			spin_lock_irqsave(&sc->lock, flags);
			sc->ds4_dongle_state = DONGLE_DISCONNECTED;
			spin_unlock_irqrestore(&sc->lock, flags);


			return 0;
		} else if (dongle_state == DONGLE_CALIBRATING ||
			   dongle_state == DONGLE_DISABLED ||
			   dongle_state == DONGLE_DISCONNECTED) {

			return 0;
		}

		dualshock4_parse_report(sc, rd, size);

	} else if ((sc->quirks & NSG_MRXU_REMOTE) && rd[0] == 0x02) {
		nsg_mrxu_parse_report(sc, rd, size);
		return 1;
	}

	if (sc->defer_initialization) {
		sc->defer_initialization = 0;
		sony_schedule_work(sc, SONY_WORKER_STATE);
	}

	return 0;
}
