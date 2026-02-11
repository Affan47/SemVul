send_keyboard_event(struct input_dev *dev,
		struct remote_input *input)
{
	unsigned int key;
	unsigned short code = input->data.keyboard.key_code;

	if (code & 0xff00)
		key = xlate_high[code & 0xff];
	else
		key = xlate[code];
	input_report_key(dev, key, input->data.keyboard.key_down);
	input_sync(dev);
}
