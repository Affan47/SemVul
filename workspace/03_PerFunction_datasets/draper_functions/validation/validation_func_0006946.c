stub_dbus_connection_add_filter(value bus, value callback)
{
	CAMLparam2(bus, callback);
	value *callbackp;

	callbackp = malloc(sizeof(value));
	if (!callbackp)
		caml_raise_out_of_memory();
	*callbackp = callback;
	caml_register_global_root(callbackp);
	dbus_connection_add_filter(DBusConnection_val(bus),
	                           add_filter_callback, callbackp,
	                           dbus_free_filter);

	CAMLreturn(Val_unit);
}
