static void hidinput_led_worker(struct work_struct *work)
{
	struct hid_device *hid = container_of(work, struct hid_device,
					      led_work);
	struct hid_field *field;
	struct hid_report *report;
	int ret;
	u32 len;
	__u8 *buf;

	field = hidinput_get_led_field(hid);
	if (!field)
		return;


	report = field->report;


	if (hid->ll_driver->request)
		return hid->ll_driver->request(hid, report, HID_REQ_SET_REPORT);


	len = hid_report_len(report);
	buf = hid_alloc_report_buf(report, GFP_KERNEL);
	if (!buf)
		return;

	hid_output_report(report, buf);

	ret = hid_hw_output_report(hid, buf, len);
	if (ret == -ENOSYS)
		hid_hw_raw_request(hid, report->id, buf, len, HID_OUTPUT_REPORT,
				HID_REQ_SET_REPORT);
	kfree(buf);
}
