cypress_set_input_params(struct input_dev *input,
				    struct cytp_data *cytp)
{
	int ret;

	if (!cytp->tp_res_x || !cytp->tp_res_y)
		return -EINVAL;

	__set_bit(EV_ABS, input->evbit);
	input_set_abs_params(input, ABS_X, 0, cytp->tp_max_abs_x, 0, 0);
	input_set_abs_params(input, ABS_Y, 0, cytp->tp_max_abs_y, 0, 0);
	input_set_abs_params(input, ABS_PRESSURE,
			     cytp->tp_min_pressure, cytp->tp_max_pressure, 0, 0);
	input_set_abs_params(input, ABS_TOOL_WIDTH, 0, 255, 0, 0);


	input_set_abs_params(input, ABS_MT_POSITION_X, 0, cytp->tp_max_abs_x, 0, 0);
	input_set_abs_params(input, ABS_MT_POSITION_Y, 0, cytp->tp_max_abs_y, 0, 0);
	input_set_abs_params(input, ABS_MT_PRESSURE, 0, 255, 0, 0);

	ret = input_mt_init_slots(input, CYTP_MAX_MT_SLOTS,
			INPUT_MT_DROP_UNUSED|INPUT_MT_TRACK);
	if (ret < 0)
		return ret;

#if ( CYPRESS_SIMULATED_MT != 1 )
	__set_bit(INPUT_PROP_SEMI_MT, input->propbit);
#endif

	input_abs_set_res(input, ABS_X, cytp->tp_res_x);
	input_abs_set_res(input, ABS_Y, cytp->tp_res_y);

	input_abs_set_res(input, ABS_MT_POSITION_X, cytp->tp_res_x);
	input_abs_set_res(input, ABS_MT_POSITION_Y, cytp->tp_res_y);

	__set_bit(BTN_TOUCH, input->keybit);
	__set_bit(BTN_TOOL_FINGER, input->keybit);
	__set_bit(BTN_TOOL_DOUBLETAP, input->keybit);
	__set_bit(BTN_TOOL_TRIPLETAP, input->keybit);
	__set_bit(BTN_TOOL_QUADTAP, input->keybit);
	__set_bit(BTN_TOOL_QUINTTAP, input->keybit);

	__clear_bit(EV_REL, input->evbit);
	__clear_bit(REL_X, input->relbit);
	__clear_bit(REL_Y, input->relbit);

	__set_bit(EV_KEY, input->evbit);
	__set_bit(BTN_LEFT, input->keybit);
	__set_bit(BTN_RIGHT, input->keybit);
	__set_bit(BTN_MIDDLE, input->keybit);

	input_set_drvdata(input, cytp);

	return 0;
}
