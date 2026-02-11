path_unregister(void *data)
{
	struct serial_device *device = data;

	DBG("Unregistered interface %s on path %s", SERIAL_PORT_INTERFACE,
		device->path);

	devices = g_slist_remove(devices, device);
	serial_device_free(device);
}
