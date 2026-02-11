max6900_i2c_read_time(struct i2c_client *client, struct rtc_time *tm)
{
	int rc;
	u8 regs[MAX6900_REG_LEN];

	rc = max6900_i2c_read_regs(client, regs);
	if (rc < 0)
		return rc;

	tm->tm_sec = bcd2bin(regs[MAX6900_REG_SC]);
	tm->tm_min = bcd2bin(regs[MAX6900_REG_MN]);
	tm->tm_hour = bcd2bin(regs[MAX6900_REG_HR] & 0x3f);
	tm->tm_mday = bcd2bin(regs[MAX6900_REG_DT]);
	tm->tm_mon = bcd2bin(regs[MAX6900_REG_MO]) - 1;
	tm->tm_year = bcd2bin(regs[MAX6900_REG_YR]) +
		      bcd2bin(regs[MAX6900_REG_CENTURY]) * 100 - 1900;
	tm->tm_wday = bcd2bin(regs[MAX6900_REG_DW]);

	return rtc_valid_tm(tm);
}
