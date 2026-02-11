read_backlight_power(struct asus_wmi *asus)
{
	int ret;
	if (asus->driver->quirks->store_backlight_power)
		ret = !asus->driver->panel_power;
	else
		ret = asus_wmi_get_devstate_simple(asus,
						   ASUS_WMI_DEVID_BACKLIGHT);

	if (ret < 0)
		return ret;

	return ret ? FB_BLANK_UNBLANK : FB_BLANK_POWERDOWN;
}
