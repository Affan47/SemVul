gck_session_derive_key_async (GckSession *self, GckObject *base, GckMechanism *mechanism,
                               GckAttributes *attrs, GCancellable *cancellable,
                               GAsyncReadyCallback callback, gpointer user_data)
{
	DeriveKey *args = _gck_call_async_prep (self, self, perform_derive_key,
	                                         NULL, sizeof (*args), free_derive_key);

	g_return_if_fail (GCK_IS_SESSION (self));
	g_return_if_fail (GCK_IS_OBJECT (base));
	g_return_if_fail (attrs);

	g_object_get (base, "handle", &args->key, NULL);
	g_return_if_fail (args->key != 0);


	memcpy (&args->mechanism, mechanism, sizeof (args->mechanism));

	args->attrs = gck_attributes_ref_sink (attrs);

	_gck_call_async_ready_go (args, cancellable, callback, user_data);
}
