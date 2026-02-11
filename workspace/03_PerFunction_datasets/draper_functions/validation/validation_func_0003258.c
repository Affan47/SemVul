uhid_hid_output_raw(struct hid_device *hid, __u8 *buf, size_t count,
			       unsigned char report_type)
{
	struct uhid_device *uhid = hid->driver_data;
	__u8 rtype;
	unsigned long flags;
	struct uhid_event *ev;

	switch (report_type) {
	case HID_FEATURE_REPORT:
		rtype = UHID_FEATURE_REPORT;
		break;
	case HID_OUTPUT_REPORT:
		rtype = UHID_OUTPUT_REPORT;
		break;
	default:
		return -EINVAL;
	}

	if (count < 1 || count > UHID_DATA_MAX)
		return -EINVAL;

	ev = kzalloc(sizeof(*ev), GFP_KERNEL);
	if (!ev)
		return -ENOMEM;

	ev->type = UHID_OUTPUT;
	ev->u.output.size = count;
	ev->u.output.rtype = rtype;
	memcpy(ev->u.output.data, buf, count);

	spin_lock_irqsave(&uhid->qlock, flags);
	uhid_queue(uhid, ev);
	spin_unlock_irqrestore(&uhid->qlock, flags);

	return count;
}
