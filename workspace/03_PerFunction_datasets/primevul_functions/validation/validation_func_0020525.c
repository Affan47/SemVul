static void hidinput_handle_scroll(struct hid_usage *usage,
				   struct input_dev *input,
				   __s32 value)
{
	int code;
	int hi_res, lo_res;

	if (value == 0)
		return;

	if (usage->code == REL_WHEEL_HI_RES)
		code = REL_WHEEL;
	else
		code = REL_HWHEEL;


	hi_res = value * 120/usage->resolution_multiplier;

	usage->wheel_accumulated += hi_res;
	lo_res = usage->wheel_accumulated/120;
	if (lo_res)
		usage->wheel_accumulated -= lo_res * 120;

	input_event(input, EV_REL, code, lo_res);
	input_event(input, EV_REL, usage->code, hi_res);
}
