mt9m111_suspend(struct mt9m111 *mt9m111)
{
	struct i2c_client *client = v4l2_get_subdevdata(&mt9m111->subdev);
	int ret;

	v4l2_ctrl_s_ctrl(mt9m111->gain, mt9m111_get_global_gain(mt9m111));

	ret = reg_set(RESET, MT9M111_RESET_RESET_MODE);
	if (!ret)
		ret = reg_set(RESET, MT9M111_RESET_RESET_SOC |
			      MT9M111_RESET_OUTPUT_DISABLE |
			      MT9M111_RESET_ANALOG_STANDBY);
	if (!ret)
		ret = reg_clear(RESET, MT9M111_RESET_CHIP_ENABLE);

	return ret;
}
