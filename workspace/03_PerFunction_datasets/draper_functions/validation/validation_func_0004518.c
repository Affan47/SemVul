reefnet_sensusultra_device_close (dc_device_t *abstract)
{
	reefnet_sensusultra_device_t *device = (reefnet_sensusultra_device_t*) abstract;


	if (serial_close (device->port) == -1) {
		free (device);
		return DC_STATUS_IO;
	}


	free (device);

	return DC_STATUS_SUCCESS;
}
