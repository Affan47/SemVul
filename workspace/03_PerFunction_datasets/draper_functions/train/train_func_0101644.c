loopback_enable(MGSLPC_INFO *info)
{
	unsigned char val;


	val = read_reg(info, CHA + CCR1) | (BIT2 | BIT1 | BIT0);
	write_reg(info, CHA + CCR1, val);


	val = read_reg(info, CHA + CCR2) | (BIT4 | BIT5);
	write_reg(info, CHA + CCR2, val);


	if (info->params.clock_speed)
		mgslpc_set_rate(info, CHA, info->params.clock_speed);
	else
		mgslpc_set_rate(info, CHA, 1843200);


	val = read_reg(info, CHA + MODE) | BIT0;
	write_reg(info, CHA + MODE, val);
}
