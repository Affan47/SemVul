omapi_message_destroy (omapi_object_t *h,
				    const char *file, int line)
{
	omapi_message_object_t *m;
	if (h -> type != omapi_type_message)
		return DHCP_R_INVALIDARG;
	m = (omapi_message_object_t *)h;
	if (m -> authenticator) {
		omapi_typed_data_dereference (&m -> authenticator, file, line);
	}
	if (!m -> prev && omapi_registered_messages != m)
		omapi_message_unregister (h);
	if (m -> id_object)
		omapi_object_dereference (&m -> id_object, file, line);
	if (m -> object)
		omapi_object_dereference (&m -> object, file, line);
	if (m -> notify_object)
		omapi_object_dereference (&m -> notify_object, file, line);
	if (m -> protocol_object)
		omapi_protocol_dereference (&m -> protocol_object, file, line);
	return ISC_R_SUCCESS;
}
