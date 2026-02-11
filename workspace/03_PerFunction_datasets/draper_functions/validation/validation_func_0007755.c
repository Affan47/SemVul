FAN_FROM_REG(u8 reg, u8 div)
{
	if (!reg)
		return -1;

	if (reg == 255)
		return 0;

	return SCALE(1350000, 1, reg * div);
}
