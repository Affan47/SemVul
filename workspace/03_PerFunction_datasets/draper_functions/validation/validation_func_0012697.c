g_mime_object_set_content_disposition_parameter (GMimeObject *object, const char *name, const char *value)
{
	GMimeContentDisposition *disposition;

	g_return_if_fail (GMIME_IS_OBJECT (object));
	g_return_if_fail (name != NULL);

	if (!object->disposition) {
		disposition = g_mime_content_disposition_new ();
		_g_mime_object_set_content_disposition (object, disposition);
		g_object_unref (disposition);
	}

	g_mime_content_disposition_set_parameter (object->disposition, name, value);
}
