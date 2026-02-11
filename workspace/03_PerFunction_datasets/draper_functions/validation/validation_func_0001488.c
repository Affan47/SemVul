_e_mod_kbd_device_dbus_chg(void *data __UNUSED__, DBusMessage *msg)
{
   DBusError err;
   char *udi, *cap;

   dbus_error_init(&err);
   dbus_message_get_args(msg, &err, DBUS_TYPE_STRING, &udi,
                         DBUS_TYPE_STRING, &cap, DBUS_TYPE_INVALID);
   if (cap)
     {
        if (!strcmp(cap, "input.keyboard"))
          {
             if (udi)
               {
                  _e_mod_kbd_device_kbd_add(udi);
                  _e_mod_kbd_device_kbd_eval();
               }
          }
     }
}
