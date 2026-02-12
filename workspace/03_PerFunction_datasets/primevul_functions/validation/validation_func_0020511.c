static int mt_resume(struct hid_device *hdev)
{


	hid_hw_idle(hdev, 0, 0, HID_REQ_SET_IDLE);

	return 0;
}
