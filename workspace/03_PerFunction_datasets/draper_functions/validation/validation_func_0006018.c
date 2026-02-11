camel_junk_filter_classify (CamelJunkFilter *junk_filter,
                            CamelMimeMessage *message,
                            GCancellable *cancellable,
                            GError **error)
{
	CamelJunkFilterInterface *interface;

	g_return_val_if_fail (CAMEL_IS_JUNK_FILTER (junk_filter), 0);
	g_return_val_if_fail (CAMEL_IS_MIME_MESSAGE (message), 0);

	interface = CAMEL_JUNK_FILTER_GET_INTERFACE (junk_filter);
	g_return_val_if_fail (interface->classify != NULL, 0);

	return interface->classify (
		junk_filter, message, cancellable, error);
}
