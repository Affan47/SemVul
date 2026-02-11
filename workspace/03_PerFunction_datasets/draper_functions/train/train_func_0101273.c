toshiba_wmi_init(void)
{
	int ret;

	if (!wmi_has_guid(WMI_EVENT_GUID) ||
	    !dmi_check_system(toshiba_wmi_dmi_table))
		return -ENODEV;

	ret = toshiba_wmi_input_setup();
	if (ret) {
		pr_err("Failed to setup input device\n");
		return ret;
	}

	pr_info("Toshiba WMI Hotkey Driver\n");

	return 0;
}
