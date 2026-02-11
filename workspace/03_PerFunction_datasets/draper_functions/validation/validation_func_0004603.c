terratec_h5_init(struct em28xx *dev)
{
	int i;
	struct em28xx_reg_seq terratec_h5_init[] = {
		{EM2820_R08_GPIO_CTRL,		0xff,	0xff,	10},
		{EM2874_R80_GPIO_P0_CTRL,	0xf6,	0xff,	100},
		{EM2874_R80_GPIO_P0_CTRL,	0xf2,	0xff,	50},
		{EM2874_R80_GPIO_P0_CTRL,	0xf6,	0xff,	100},
		{	-1,			-1,	-1,	-1},
	};
	struct em28xx_reg_seq terratec_h5_end[] = {
		{EM2874_R80_GPIO_P0_CTRL,	0xe6,	0xff,	100},
		{EM2874_R80_GPIO_P0_CTRL,	0xa6,	0xff,	50},
		{EM2874_R80_GPIO_P0_CTRL,	0xe6,	0xff,	100},
		{	-1,			-1,	-1,	-1},
	};
	struct {
		unsigned char r[4];
		int len;
	} regs[] = {
		{{ 0x06, 0x02, 0x00, 0x31 }, 4},
		{{ 0x01, 0x02 }, 2},
		{{ 0x01, 0x02, 0x00, 0xc6 }, 4},
		{{ 0x01, 0x00 }, 2},
		{{ 0x01, 0x00, 0xff, 0xaf }, 4},
		{{ 0x01, 0x00, 0x03, 0xa0 }, 4},
		{{ 0x01, 0x00 }, 2},
		{{ 0x01, 0x00, 0x73, 0xaf }, 4},
		{{ 0x04, 0x00 }, 2},
		{{ 0x00, 0x04 }, 2},
		{{ 0x00, 0x04, 0x00, 0x0a }, 4},
		{{ 0x04, 0x14 }, 2},
		{{ 0x04, 0x14, 0x00, 0x00 }, 4},
	};

	em28xx_gpio_set(dev, terratec_h5_init);
	em28xx_write_reg(dev, EM28XX_R06_I2C_CLK, 0x40);
	msleep(10);
	em28xx_write_reg(dev, EM28XX_R06_I2C_CLK, 0x45);
	msleep(10);

	dev->i2c_client[dev->def_i2c_bus].addr = 0x82 >> 1;

	for (i = 0; i < ARRAY_SIZE(regs); i++)
		i2c_master_send(&dev->i2c_client[dev->def_i2c_bus], regs[i].r, regs[i].len);
	em28xx_gpio_set(dev, terratec_h5_end);
}
