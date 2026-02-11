bq2415x_set_defaults(struct bq2415x_device *bq)
{
	bq2415x_exec_command(bq, BQ2415X_BOOST_MODE_DISABLE);
	bq2415x_exec_command(bq, BQ2415X_CHARGER_DISABLE);
	bq2415x_exec_command(bq, BQ2415X_CHARGE_TERMINATION_DISABLE);

	bq2415x_set_default_value(bq, current_limit);
	bq2415x_set_default_value(bq, weak_battery_voltage);
	bq2415x_set_default_value(bq, battery_regulation_voltage);

	if (bq->init_data.resistor_sense > 0) {
		bq2415x_set_default_value(bq, charge_current);
		bq2415x_set_default_value(bq, termination_current);
		bq2415x_exec_command(bq, BQ2415X_CHARGE_TERMINATION_ENABLE);
	}

	bq2415x_exec_command(bq, BQ2415X_CHARGER_ENABLE);
	return 0;
}
