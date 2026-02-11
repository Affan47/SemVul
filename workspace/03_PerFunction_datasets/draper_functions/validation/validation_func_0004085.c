debugfs_status_show(struct seq_file *s, void *data)
{
	struct ideapad_private *priv = s->private;
	unsigned long value;

	if (!priv)
		return -EINVAL;

	if (!read_ec_data(priv->adev->handle, VPCCMD_R_BL_MAX, &value))
		seq_printf(s, "Backlight max:\t%lu\n", value);
	if (!read_ec_data(priv->adev->handle, VPCCMD_R_BL, &value))
		seq_printf(s, "Backlight now:\t%lu\n", value);
	if (!read_ec_data(priv->adev->handle, VPCCMD_R_BL_POWER, &value))
		seq_printf(s, "BL power value:\t%s\n", value ? "On" : "Off");
	seq_printf(s, "=====================\n");

	if (!read_ec_data(priv->adev->handle, VPCCMD_R_RF, &value))
		seq_printf(s, "Radio status:\t%s(%lu)\n",
			   value ? "On" : "Off", value);
	if (!read_ec_data(priv->adev->handle, VPCCMD_R_WIFI, &value))
		seq_printf(s, "Wifi status:\t%s(%lu)\n",
			   value ? "On" : "Off", value);
	if (!read_ec_data(priv->adev->handle, VPCCMD_R_BT, &value))
		seq_printf(s, "BT status:\t%s(%lu)\n",
			   value ? "On" : "Off", value);
	if (!read_ec_data(priv->adev->handle, VPCCMD_R_3G, &value))
		seq_printf(s, "3G status:\t%s(%lu)\n",
			   value ? "On" : "Off", value);
	seq_printf(s, "=====================\n");

	if (!read_ec_data(priv->adev->handle, VPCCMD_R_TOUCHPAD, &value))
		seq_printf(s, "Touchpad status:%s(%lu)\n",
			   value ? "On" : "Off", value);
	if (!read_ec_data(priv->adev->handle, VPCCMD_R_CAMERA, &value))
		seq_printf(s, "Camera status:\t%s(%lu)\n",
			   value ? "On" : "Off", value);

	return 0;
}
