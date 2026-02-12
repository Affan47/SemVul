static int sony_register_sensors(struct sony_sc *sc)
{
	size_t name_sz;
	char *name;
	int ret;
	int range;

	sc->sensor_dev = devm_input_allocate_device(&sc->hdev->dev);
	if (!sc->sensor_dev)
		return -ENOMEM;

	input_set_drvdata(sc->sensor_dev, sc);
	sc->sensor_dev->dev.parent = &sc->hdev->dev;
	sc->sensor_dev->phys = sc->hdev->phys;
	sc->sensor_dev->uniq = sc->hdev->uniq;
	sc->sensor_dev->id.bustype = sc->hdev->bus;
	sc->sensor_dev->id.vendor = sc->hdev->vendor;
	sc->sensor_dev->id.product = sc->hdev->product;
	sc->sensor_dev->id.version = sc->hdev->version;


	name_sz = strlen(sc->hdev->name) + sizeof(SENSOR_SUFFIX);
	name = devm_kzalloc(&sc->hdev->dev, name_sz, GFP_KERNEL);
	if (!name)
		return -ENOMEM;
	snprintf(name, name_sz, "%s" SENSOR_SUFFIX, sc->hdev->name);
	sc->sensor_dev->name = name;

	if (sc->quirks & SIXAXIS_CONTROLLER) {


		input_set_abs_params(sc->sensor_dev, ABS_X, -512, 511, 4, 0);
		input_set_abs_params(sc->sensor_dev, ABS_Y, -512, 511, 4, 0);
		input_set_abs_params(sc->sensor_dev, ABS_Z, -512, 511, 4, 0);
		input_abs_set_res(sc->sensor_dev, ABS_X, SIXAXIS_ACC_RES_PER_G);
		input_abs_set_res(sc->sensor_dev, ABS_Y, SIXAXIS_ACC_RES_PER_G);
		input_abs_set_res(sc->sensor_dev, ABS_Z, SIXAXIS_ACC_RES_PER_G);
	} else if (sc->quirks & DUALSHOCK4_CONTROLLER) {
		range = DS4_ACC_RES_PER_G*4;
		input_set_abs_params(sc->sensor_dev, ABS_X, -range, range, 16, 0);
		input_set_abs_params(sc->sensor_dev, ABS_Y, -range, range, 16, 0);
		input_set_abs_params(sc->sensor_dev, ABS_Z, -range, range, 16, 0);
		input_abs_set_res(sc->sensor_dev, ABS_X, DS4_ACC_RES_PER_G);
		input_abs_set_res(sc->sensor_dev, ABS_Y, DS4_ACC_RES_PER_G);
		input_abs_set_res(sc->sensor_dev, ABS_Z, DS4_ACC_RES_PER_G);

		range = DS4_GYRO_RES_PER_DEG_S*2048;
		input_set_abs_params(sc->sensor_dev, ABS_RX, -range, range, 16, 0);
		input_set_abs_params(sc->sensor_dev, ABS_RY, -range, range, 16, 0);
		input_set_abs_params(sc->sensor_dev, ABS_RZ, -range, range, 16, 0);
		input_abs_set_res(sc->sensor_dev, ABS_RX, DS4_GYRO_RES_PER_DEG_S);
		input_abs_set_res(sc->sensor_dev, ABS_RY, DS4_GYRO_RES_PER_DEG_S);
		input_abs_set_res(sc->sensor_dev, ABS_RZ, DS4_GYRO_RES_PER_DEG_S);

		__set_bit(EV_MSC, sc->sensor_dev->evbit);
		__set_bit(MSC_TIMESTAMP, sc->sensor_dev->mscbit);
	}

	__set_bit(INPUT_PROP_ACCELEROMETER, sc->sensor_dev->propbit);

	ret = input_register_device(sc->sensor_dev);
	if (ret < 0)
		return ret;

	return 0;
}
