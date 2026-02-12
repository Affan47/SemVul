static void mt_process_mt_event(struct hid_device *hid,
				struct mt_application *app,
				struct hid_field *field,
				struct hid_usage *usage,
				__s32 value,
				bool first_packet)
{
	__s32 quirks = app->quirks;
	struct input_dev *input = field->hidinput->input;

	if (!usage->type || !(hid->claimed & HID_CLAIMED_INPUT))
		return;

	if (quirks & MT_QUIRK_WIN8_PTP_BUTTONS) {


		if (!first_packet)
			return;


		if (usage->type == EV_KEY && usage->code == BTN_LEFT) {
			app->left_button_state |= value;
			return;
		}
	}

	input_event(input, usage->type, usage->code, value);
}
