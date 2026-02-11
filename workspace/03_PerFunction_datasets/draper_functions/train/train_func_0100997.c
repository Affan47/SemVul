cm_tdbusm_get_as(DBusMessage *msg, void *parent, char ***as)
{
	DBusError err;
	char **tmp;
	int i;
	*as = NULL;
	dbus_error_init(&err);
	if (dbus_message_get_args(msg, &err,
				  DBUS_TYPE_ARRAY, DBUS_TYPE_STRING, &tmp, &i,
				  DBUS_TYPE_INVALID)) {
		*as = cm_tdbusm_take_dbus_string_array(parent, tmp, i);
		return 0;
	} else {
		if (dbus_error_is_set(&err)) {
			dbus_error_free(&err);
			dbus_error_init(&err);
		}
		return -1;
	}
}
