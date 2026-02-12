static int mt_input_mapping(struct hid_device *hdev, struct hid_input *hi,
		struct hid_field *field, struct hid_usage *usage,
		unsigned long **bit, int *max)
{
	struct mt_device *td = hid_get_drvdata(hdev);
	struct mt_application *application;
	struct mt_report_data *rdata;

	rdata = mt_find_report_data(td, field->report);
	if (!rdata) {
		hid_err(hdev, "failed to allocate data for report\n");
		return 0;
	}

	application = rdata->application;


	if (!td->mtclass.export_all_inputs &&
	    field->application != HID_DG_TOUCHSCREEN &&
	    field->application != HID_DG_PEN &&
	    field->application != HID_DG_TOUCHPAD &&
	    field->application != HID_GD_KEYBOARD &&
	    field->application != HID_GD_SYSTEM_CONTROL &&
	    field->application != HID_CP_CONSUMER_CONTROL &&
	    field->application != HID_GD_WIRELESS_RADIO_CTLS &&
	    field->application != HID_GD_SYSTEM_MULTIAXIS &&
	    !(field->application == HID_VD_ASUS_CUSTOM_MEDIA_KEYS &&
	      application->quirks & MT_QUIRK_ASUS_CUSTOM_UP))
		return -1;


	if (field->application == HID_VD_ASUS_CUSTOM_MEDIA_KEYS &&
	    application->quirks & MT_QUIRK_ASUS_CUSTOM_UP &&
	    (usage->hid & HID_USAGE_PAGE) == HID_UP_CUSTOM) {
		set_bit(EV_REP, hi->input->evbit);
		if (field->flags & HID_MAIN_ITEM_VARIABLE)
			field->flags &= ~HID_MAIN_ITEM_VARIABLE;
		switch (usage->hid & HID_USAGE) {
		case 0x10: mt_map_key_clear(KEY_BRIGHTNESSDOWN);	break;
		case 0x20: mt_map_key_clear(KEY_BRIGHTNESSUP);		break;
		case 0x35: mt_map_key_clear(KEY_DISPLAY_OFF);		break;
		case 0x6b: mt_map_key_clear(KEY_F21);			break;
		case 0x6c: mt_map_key_clear(KEY_SLEEP);			break;
		default:
			return -1;
		}
		return 1;
	}

	if (rdata->is_mt_collection)
		return mt_touch_input_mapping(hdev, hi, field, usage, bit, max,
					      application);


	if (field->physical == HID_DG_STYLUS)
		hi->application = HID_DG_STYLUS;


	return 0;
}
