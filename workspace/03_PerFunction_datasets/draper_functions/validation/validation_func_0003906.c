_default_adapter_callback(__UNUSED__ void *data, DBusMessage *msg, __UNUSED__ DBusError *err)
{
   E_Bluez_Element *element;
   const char *path;

   if (dbus_message_get_args(msg, NULL, DBUS_TYPE_OBJECT_PATH, &path,
                           DBUS_TYPE_INVALID) == EINA_FALSE)
           printf("FAILURE: failed to get default adapter\n");

   printf("SUCCESS: default adapter: %s\n", path);

   element = e_bluez_element_get(path);
   e_bluez_element_print(stdout, element);
   return;

}
