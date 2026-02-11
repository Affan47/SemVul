jack_engine_load_driver (jack_engine_t *engine,
			 jack_driver_desc_t * driver_desc,
			 JSList * driver_params)
{
	jack_client_internal_t *client;
	jack_driver_t *driver;
	jack_driver_info_t *info;

	if ((info = jack_load_driver (engine, driver_desc)) == NULL) {
		return -1;
	}

	if ((client = jack_create_driver_client (engine, info->client_name)
		    ) == NULL) {
		return -1;
	}

	if ((driver = info->initialize (client->private_client,
					driver_params)) == NULL) {
		free (info);
		return -1;
	}

	driver->handle = info->handle;
	driver->finish = info->finish;
	driver->internal_client = client;
	free (info);

	if (jack_use_driver (engine, driver) < 0) {
		jack_remove_client (engine, client);
		return -1;
	}

	engine->driver_desc   = driver_desc;
	engine->driver_params = driver_params;

	if (engine->control->real_time) {
		if (jack_start_watchdog (engine)) {
			return -1;
		}
		engine->watchdog_check = 1;
	}
	return 0;
}
