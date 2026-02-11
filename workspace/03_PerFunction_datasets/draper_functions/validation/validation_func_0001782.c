sdcmd_CS(const void *foo)
{
	int ret;
	char temp[APC_SBUF];

	upsdebugx(1, "using CS 350 'force OB' shutdown method");
	if (ups_status & APC_STAT_OL) {
		apc_flush(0);
		upsdebugx(1, "status OL - forcing OB temporarily");
		ret = apc_write(APC_CMD_SIMPWF);
		if (ret < 0) {
			upslog_with_errno(LOG_ERR, "sdcmd_CS: issuing 'U' failed");
			return STAT_INSTCMD_FAILED;
		}

		ret = apc_read(temp, sizeof(temp), SER_D1);
		if (ret < 0) {
			upslog_with_errno(LOG_ERR, "sdcmd_CS: 'U' returned nothing ?");
			return STAT_INSTCMD_FAILED;
		}
	}
	return sdcmd_S(0);
}
