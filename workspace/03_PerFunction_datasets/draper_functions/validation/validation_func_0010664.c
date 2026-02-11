midway_serial_pic_w(UINT8 data)
{
	logerror("%08X:security W = %04X\n", activecpu_get_pc(), data);


	serial.status = (data >> 4) & 1;


	if (!serial.status)
	{


		if (data & 0x0f)
			serial.buffer = serial.ormask | data;
		else
			serial.buffer = serial.data[serial.index++ % sizeof(serial.data)];
	}
}
