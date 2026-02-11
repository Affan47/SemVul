atk_enumerate_new_hwmon(struct atk_data *data)
{
	struct device *dev = &data->acpi_dev->dev;
	union acpi_object *pack;
	int err;
	int i;

	err = atk_ec_present(data);
	if (err < 0)
		return err;
	if (err) {
		err = atk_ec_enabled(data);
		if (err < 0)
			return err;

		data->disable_ec = err;

		err = atk_ec_ctl(data, 1);
		if (err) {
			data->disable_ec = false;
			return err;
		}
	}

	dev_dbg(dev, "Enumerating hwmon sensors\n");

	pack = atk_ggrp(data, ATK_MUX_HWMON);
	if (IS_ERR(pack))
		return PTR_ERR(pack);

	for (i = 0; i < pack->package.count; i++) {
		union acpi_object *obj = &pack->package.elements[i];

		atk_add_sensor(data, obj);
	}

	err = data->voltage_count + data->temperature_count + data->fan_count;

	ACPI_FREE(pack);
	return err;
}
