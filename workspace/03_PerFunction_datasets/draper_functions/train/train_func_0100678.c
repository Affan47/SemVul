bus_service_unlink (BusService *service)
{
  _dbus_assert (service->owners == NULL);


  _dbus_hash_table_remove_string (service->registry->service_hash,
                                  service->name);

  bus_service_unref (service);
}
