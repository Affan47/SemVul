static void mt_touch_report(struct hid_device *hid,
			    struct mt_report_data *rdata)
{
	struct mt_device *td = hid_get_drvdata(hid);
	struct hid_report *report = rdata->report;
	struct mt_application *app = rdata->application;
	struct hid_field *field;
	struct input_dev *input;
	struct mt_usages *slot;
	bool first_packet;
	unsigned count;
	int r, n;
	int scantime = 0;
	int contact_count = -1;


	if (test_and_set_bit(MT_IO_FLAGS_RUNNING, &td->mt_io_flags))
		return;

	scantime = *app->scantime;
	app->timestamp = mt_compute_timestamp(app, scantime);
	if (app->raw_cc != DEFAULT_ZERO)
		contact_count = *app->raw_cc;


	if (contact_count >= 0) {


		if ((app->quirks & MT_QUIRK_WIN8_PTP_BUTTONS) &&
		    app->num_received == 0 &&
		    app->prev_scantime != scantime)
			app->num_expected = contact_count;

		else if (contact_count)
			app->num_expected = contact_count;
	}
	app->prev_scantime = scantime;

	first_packet = app->num_received == 0;

	input = report->field[0]->hidinput->input;

	list_for_each_entry(slot, &app->mt_usages, list) {
		if (!mt_process_slot(td, input, app, slot))
			app->num_received++;
	}

	for (r = 0; r < report->maxfield; r++) {
		field = report->field[r];
		count = field->report_count;

		if (!(HID_MAIN_ITEM_VARIABLE & field->flags))
			continue;

		for (n = 0; n < count; n++)
			mt_process_mt_event(hid, app, field,
					    &field->usage[n], field->value[n],
					    first_packet);
	}

	if (app->num_received >= app->num_expected)
		mt_sync_frame(td, app, input);


	if (app->quirks & MT_QUIRK_STICKY_FINGERS) {
		if (test_bit(MT_IO_FLAGS_PENDING_SLOTS, &td->mt_io_flags))
			mod_timer(&td->release_timer,
				  jiffies + msecs_to_jiffies(100));
		else
			del_timer(&td->release_timer);
	}

	clear_bit(MT_IO_FLAGS_RUNNING, &td->mt_io_flags);
}
