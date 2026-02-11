em28xx_probe_sensor_micron(struct em28xx *dev)
{
	int ret, i;
	char *name;
	u8 reg;
	__be16 id_be;
	u16 id;

	struct i2c_client client = dev->i2c_client[dev->def_i2c_bus];

	dev->em28xx_sensor = EM28XX_NOSENSOR;
	for (i = 0; micron_sensor_addrs[i] != I2C_CLIENT_END; i++) {
		client.addr = micron_sensor_addrs[i];


		reg = 0x00;
		ret = i2c_master_send(&client, &reg, 1);
		if (ret < 0) {
			if (ret != -ENXIO)
				em28xx_errdev("couldn't read from i2c device 0x%02x: error %i\n",
					      client.addr << 1, ret);
			continue;
		}
		ret = i2c_master_recv(&client, (u8 *)&id_be, 2);
		if (ret < 0) {
			em28xx_errdev("couldn't read from i2c device 0x%02x: error %i\n",
				      client.addr << 1, ret);
			continue;
		}
		id = be16_to_cpu(id_be);

		reg = 0xff;
		ret = i2c_master_send(&client, &reg, 1);
		if (ret < 0) {
			em28xx_errdev("couldn't read from i2c device 0x%02x: error %i\n",
				      client.addr << 1, ret);
			continue;
		}
		ret = i2c_master_recv(&client, (u8 *)&id_be, 2);
		if (ret < 0) {
			em28xx_errdev("couldn't read from i2c device 0x%02x: error %i\n",
				      client.addr << 1, ret);
			continue;
		}

		if (id != be16_to_cpu(id_be))
			continue;

		id = be16_to_cpu(id_be);
		switch (id) {
		case 0x1222:
			name = "MT9V012";
			break;
		case 0x1229:
			name = "MT9V112";
			break;
		case 0x1433:
			name = "MT9M011";
			break;
		case 0x143a:
			name = "MT9M111";
			dev->em28xx_sensor = EM28XX_MT9M111;
			break;
		case 0x148c:
			name = "MT9M112";
			break;
		case 0x1511:
			name = "MT9D011";
			break;
		case 0x8232:
		case 0x8243:
			name = "MT9V011";
			dev->em28xx_sensor = EM28XX_MT9V011;
			break;
		case 0x8431:
			name = "MT9M001";
			dev->em28xx_sensor = EM28XX_MT9M001;
			break;
		default:
			em28xx_info("unknown Micron sensor detected: 0x%04x\n",
				    id);
			return 0;
		}

		if (dev->em28xx_sensor == EM28XX_NOSENSOR)
			em28xx_info("unsupported sensor detected: %s\n", name);
		else
			em28xx_info("sensor %s detected\n", name);

		dev->i2c_client[dev->def_i2c_bus].addr = client.addr;
		return 0;
	}

	return -ENODEV;
}
