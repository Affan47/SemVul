light_init(struct ibm_init_struct *iibm)
{
	int rc;

	vdbg_printk(TPACPI_DBG_INIT, "initializing light subdriver\n");

	if (tpacpi_is_ibm()) {
		TPACPI_ACPIHANDLE_INIT(ledb);
		TPACPI_ACPIHANDLE_INIT(lght);
	}
	TPACPI_ACPIHANDLE_INIT(cmos);
	INIT_WORK(&tpacpi_led_thinklight.work, light_set_status_worker);


	tp_features.light = (cmos_handle || lght_handle) && !ledb_handle;

	if (tp_features.light)


		tp_features.light_status =
			acpi_evalf(ec_handle, NULL, "KBLT", "qv");

	vdbg_printk(TPACPI_DBG_INIT, "light is %s, light status is %s\n",
		str_supported(tp_features.light),
		str_supported(tp_features.light_status));

	if (!tp_features.light)
		return 1;

	rc = led_classdev_register(&tpacpi_pdev->dev,
				   &tpacpi_led_thinklight.led_classdev);

	if (rc < 0) {
		tp_features.light = 0;
		tp_features.light_status = 0;
	} else  {
		rc = 0;
	}

	return rc;
}
