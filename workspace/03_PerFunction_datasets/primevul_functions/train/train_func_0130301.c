static int pb0100_init(struct sd *sd)
{
	stv06xx_write_bridge(sd, STV_REG00, 1);
	stv06xx_write_bridge(sd, STV_SCAN_RATE, 0);


	stv06xx_write_sensor(sd, PB_RESET, 1);
	stv06xx_write_sensor(sd, PB_RESET, 0);


	stv06xx_write_sensor(sd, PB_CONTROL, BIT(5)|BIT(3));


	stv06xx_write_sensor(sd, PB_PREADCTRL, BIT(12)|BIT(10)|BIT(6));
	stv06xx_write_sensor(sd, PB_ADCGLOBALGAIN, 12);


	stv06xx_write_sensor(sd, PB_R28, 12);

	stv06xx_write_sensor(sd, PB_ADCMAXGAIN, 180);

	stv06xx_write_sensor(sd, PB_ADCMINGAIN, 12);


	stv06xx_write_sensor(sd, PB_R54, 3);


	stv06xx_write_sensor(sd, PB_R55, 0);
	stv06xx_write_sensor(sd, PB_UPDATEINT, 1);

	stv06xx_write_sensor(sd, PB_R15, 800);

	stv06xx_write_sensor(sd, PB_R17, 10);

	stv06xx_write_sensor(sd, PB_EXPGAIN, 0);


	stv06xx_write_sensor(sd, PB_VOFFSET, 0);

	stv06xx_write_sensor(sd, PB_ADCGAINH, 11);

	stv06xx_write_sensor(sd, PB_ADCGAINL, 0);


	stv06xx_write_bridge(sd, STV_REG00, 0x11);
	stv06xx_write_bridge(sd, STV_REG03, 0x45);
	stv06xx_write_bridge(sd, STV_REG04, 0x07);


	stv06xx_write_sensor(sd, PB_ROWSPEED, BIT(4)|BIT(3)|BIT(1));
	stv06xx_write_sensor(sd, PB_CFILLIN, 14);
	stv06xx_write_sensor(sd, PB_VBL, 0);
	stv06xx_write_sensor(sd, PB_FINTTIME, 0);
	stv06xx_write_sensor(sd, PB_RINTTIME, 123);

	stv06xx_write_bridge(sd, STV_REG01, 0xc2);
	stv06xx_write_bridge(sd, STV_REG02, 0xb0);
	return 0;
}
