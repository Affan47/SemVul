static void dualshock4_parse_report(struct sony_sc *sc, u8 *rd, int size)
{
	struct hid_input *hidinput = list_entry(sc->hdev->inputs.next,
						struct hid_input, list);
	struct input_dev *input_dev = hidinput->input;
	unsigned long flags;
	int n, m, offset, num_touch_data, max_touch_data;
	u8 cable_state, battery_capacity, battery_charging;
	u16 timestamp;


	int data_offset = (sc->quirks & DUALSHOCK4_CONTROLLER_BT) ? 2 : 0;


	offset = data_offset + DS4_INPUT_REPORT_BUTTON_OFFSET;
	input_report_key(sc->touchpad, BTN_LEFT, rd[offset+2] & 0x2);


	if (rd[0] == 17) {
		int value;

		offset = data_offset + DS4_INPUT_REPORT_AXIS_OFFSET;
		input_report_abs(input_dev, ABS_X, rd[offset]);
		input_report_abs(input_dev, ABS_Y, rd[offset+1]);
		input_report_abs(input_dev, ABS_RX, rd[offset+2]);
		input_report_abs(input_dev, ABS_RY, rd[offset+3]);

		value = rd[offset+4] & 0xf;
		if (value > 7)
			value = 8;
		input_report_abs(input_dev, ABS_HAT0X, ds4_hat_mapping[value].x);
		input_report_abs(input_dev, ABS_HAT0Y, ds4_hat_mapping[value].y);

		input_report_key(input_dev, BTN_WEST, rd[offset+4] & 0x10);
		input_report_key(input_dev, BTN_SOUTH, rd[offset+4] & 0x20);
		input_report_key(input_dev, BTN_EAST, rd[offset+4] & 0x40);
		input_report_key(input_dev, BTN_NORTH, rd[offset+4] & 0x80);

		input_report_key(input_dev, BTN_TL, rd[offset+5] & 0x1);
		input_report_key(input_dev, BTN_TR, rd[offset+5] & 0x2);
		input_report_key(input_dev, BTN_TL2, rd[offset+5] & 0x4);
		input_report_key(input_dev, BTN_TR2, rd[offset+5] & 0x8);
		input_report_key(input_dev, BTN_SELECT, rd[offset+5] & 0x10);
		input_report_key(input_dev, BTN_START, rd[offset+5] & 0x20);
		input_report_key(input_dev, BTN_THUMBL, rd[offset+5] & 0x40);
		input_report_key(input_dev, BTN_THUMBR, rd[offset+5] & 0x80);

		input_report_key(input_dev, BTN_MODE, rd[offset+6] & 0x1);

		input_report_abs(input_dev, ABS_Z, rd[offset+7]);
		input_report_abs(input_dev, ABS_RZ, rd[offset+8]);

		input_sync(input_dev);
	}


	offset = data_offset + DS4_INPUT_REPORT_TIMESTAMP_OFFSET;
	timestamp = get_unaligned_le16(&rd[offset]);
	if (!sc->timestamp_initialized) {
		sc->timestamp_us = ((unsigned int)timestamp * 16) / 3;
		sc->timestamp_initialized = true;
	} else {
		u16 delta;

		if (sc->prev_timestamp > timestamp)
			delta = (U16_MAX - sc->prev_timestamp + timestamp + 1);
		else
			delta = timestamp - sc->prev_timestamp;
		sc->timestamp_us += (delta * 16) / 3;
	}
	sc->prev_timestamp = timestamp;
	input_event(sc->sensor_dev, EV_MSC, MSC_TIMESTAMP, sc->timestamp_us);

	offset = data_offset + DS4_INPUT_REPORT_GYRO_X_OFFSET;
	for (n = 0; n < 6; n++) {

		int raw_data = (short)((rd[offset+1] << 8) | rd[offset]);
		struct ds4_calibration_data *calib = &sc->ds4_calib_data[n];


		int calib_data = mult_frac(calib->sens_numer,
					   raw_data - calib->bias,
					   calib->sens_denom);

		input_report_abs(sc->sensor_dev, calib->abs_code, calib_data);
		offset += 2;
	}
	input_sync(sc->sensor_dev);


	offset = data_offset + DS4_INPUT_REPORT_BATTERY_OFFSET;
	cable_state = (rd[offset] >> 4) & 0x01;
	battery_capacity = rd[offset] & 0x0F;


	if (!cable_state || battery_capacity > 10)
		battery_charging = 0;
	else
		battery_charging = 1;

	if (!cable_state)
		battery_capacity++;
	if (battery_capacity > 10)
		battery_capacity = 10;

	battery_capacity *= 10;

	spin_lock_irqsave(&sc->lock, flags);
	sc->cable_state = cable_state;
	sc->battery_capacity = battery_capacity;
	sc->battery_charging = battery_charging;
	spin_unlock_irqrestore(&sc->lock, flags);


	offset = data_offset + DS4_INPUT_REPORT_TOUCHPAD_OFFSET;
	max_touch_data = (sc->quirks & DUALSHOCK4_CONTROLLER_BT) ? 4 : 3;
	if (rd[offset] > 0 && rd[offset] <= max_touch_data)
		num_touch_data = rd[offset];
	else
		num_touch_data = 1;
	offset += 1;

	for (m = 0; m < num_touch_data; m++) {

		offset += 1;


		for (n = 0; n < 2; n++) {
			u16 x, y;
			bool active;

			x = rd[offset+1] | ((rd[offset+2] & 0xF) << 8);
			y = ((rd[offset+2] & 0xF0) >> 4) | (rd[offset+3] << 4);

			active = !(rd[offset] >> 7);
			input_mt_slot(sc->touchpad, n);
			input_mt_report_slot_state(sc->touchpad, MT_TOOL_FINGER, active);

			if (active) {
				input_report_abs(sc->touchpad, ABS_MT_POSITION_X, x);
				input_report_abs(sc->touchpad, ABS_MT_POSITION_Y, y);
			}

			offset += 4;
		}
		input_mt_sync_frame(sc->touchpad);
		input_sync(sc->touchpad);
	}
}
