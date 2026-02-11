s5k83a_start(struct sd *sd)
{
	int i, err = 0;


	sd->rotation_thread = kthread_create(rotation_thread_function,
					     sd, "rotation thread");
	wake_up_process(sd->rotation_thread);


	for (i = 0; i < ARRAY_SIZE(start_s5k83a) && !err; i++) {
		u8 data[2] = {start_s5k83a[i][2], start_s5k83a[i][3]};
		if (start_s5k83a[i][0] == SENSOR)
			err = m5602_write_sensor(sd, start_s5k83a[i][1],
				data, 2);
		else
			err = m5602_write_bridge(sd, start_s5k83a[i][1],
				data[0]);
	}
	if (err < 0)
		return err;

	return s5k83a_set_led_indication(sd, 1);
}
