static int hidpp10_battery_mileage_map_status(u8 param)
{
	int status;

	switch (param >> 6) {
	case 0x00:

		status = POWER_SUPPLY_STATUS_DISCHARGING;
		break;
	case 0x01:
		status = POWER_SUPPLY_STATUS_CHARGING;
		break;
	case 0x02:
		status = POWER_SUPPLY_STATUS_FULL;
		break;


	default:
		status = POWER_SUPPLY_STATUS_NOT_CHARGING;
		break;
	}

	return status;
}
