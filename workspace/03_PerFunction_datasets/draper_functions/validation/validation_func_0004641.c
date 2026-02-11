gc_web_service_set_base_url (GcWebService *self, gchar *url)
{
	g_assert (url);

	gc_web_service_reset (self);

	g_free (self->base_url);
	self->base_url = g_strdup (url);
}
