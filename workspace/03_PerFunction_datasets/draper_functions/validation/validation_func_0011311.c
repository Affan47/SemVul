cressi_edy_device_open (dc_device_t **out, dc_context_t *context, const char *name)
{
	if (out == NULL)
		return DC_STATUS_INVALIDARGS;


	cressi_edy_device_t *device = (cressi_edy_device_t *) malloc (sizeof (cressi_edy_device_t));
	if (device == NULL) {
		ERROR (context, "Failed to allocate memory.");
		return DC_STATUS_NOMEMORY;
	}


	device_init (&device->base, context, &cressi_edy_device_vtable);


	device->port = NULL;
	device->model = 0;


	int rc = serial_open (&device->port, context, name);
	if (rc == -1) {
		ERROR (context, "Failed to open the serial port.");
		free (device);
		return DC_STATUS_IO;
	}


	rc = serial_configure (device->port, 1200, 8, SERIAL_PARITY_NONE, 1, SERIAL_FLOWCONTROL_NONE);
	if (rc == -1) {
		ERROR (context, "Failed to set the terminal attributes.");
		serial_close (device->port);
		free (device);
		return DC_STATUS_IO;
	}


	if (serial_set_timeout (device->port, 1000) == -1) {
		ERROR (context, "Failed to set the timeout.");
		serial_close (device->port);
		free (device);
		return DC_STATUS_IO;
	}


	if (serial_set_dtr (device->port, 1) == -1 ||
		serial_set_rts (device->port, 0) == -1) {
		ERROR (context, "Failed to set the DTR/RTS line.");
		serial_close (device->port);
		free (device);
		return DC_STATUS_IO;
	}


	cressi_edy_init1 (device);
	cressi_edy_init2 (device);
	cressi_edy_init3 (device);


	rc = serial_configure (device->port, 4800, 8, SERIAL_PARITY_NONE, 1, SERIAL_FLOWCONTROL_NONE);
	if (rc == -1) {
		ERROR (context, "Failed to set the terminal attributes.");
		serial_close (device->port);
		free (device);
		return DC_STATUS_IO;
	}

	*out = (dc_device_t*) device;

	return DC_STATUS_SUCCESS;
}
