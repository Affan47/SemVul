e_dbus_interface_new(const char *interface)
{
  E_DBus_Interface *iface;

  if (!interface) return NULL;

  iface = calloc(1, sizeof(E_DBus_Interface));
  if (!iface) return NULL;

  iface->refcount = 1;
  iface->name = strdup(interface);
  iface->methods = NULL;
  iface->signals = NULL;

  return iface;
}
