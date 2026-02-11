bcd2hour(u8 bcd)
{
	if (bcd & DS1305_HR_12) {
		unsigned	hour = 0;

		bcd &= ~DS1305_HR_12;
		if (bcd & DS1305_HR_PM) {
			hour = 12;
			bcd &= ~DS1305_HR_PM;
		}
		hour += bcd2bin(bcd);
		return hour - 1;
	}
	return bcd2bin(bcd);
}
