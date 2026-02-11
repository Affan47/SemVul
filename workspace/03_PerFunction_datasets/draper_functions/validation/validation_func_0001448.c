upsdrv_shutdown(void)
{
	char	temp[APC_LBUF];
	int	ret;

	if (!smartmode(1))
		upsdebugx(1, "SM detection failed. Trying a shutdown command anyway");


	ret = apc_write(APC_STATUS);

	if (ret == 1) {
		ret = apc_read(temp, sizeof(temp), SER_D1);

		if (ret < 1) {
			upsdebugx(1, "status read failed ! assuming on battery state");
			ups_status = APC_STAT_LB | APC_STAT_OB;
		} else {
			ups_status = strtol(temp, 0, 16);
		}

	} else {
		upsdebugx(1, "status request failed; assuming on battery state");
		ups_status = APC_STAT_LB | APC_STAT_OB;
	}

	if (testvar("advorder") && strcasecmp(getval("advorder"), "no"))
		upsdrv_shutdown_advanced();
	else
		upsdrv_shutdown_simple();
}
