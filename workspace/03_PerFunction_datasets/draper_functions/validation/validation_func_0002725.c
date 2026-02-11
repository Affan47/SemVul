crypt_async (GckSession *self, GckObject *key, GckMechanism *mechanism, const guchar *input,
             gsize n_input, GCancellable *cancellable, GAsyncReadyCallback callback, gpointer user_data,
             CK_C_EncryptInit init_func, CK_C_Encrypt complete_func)
{
	Crypt *args = _gck_call_async_prep (self, self, perform_crypt, NULL, sizeof (*args), free_crypt);

	g_return_if_fail (GCK_IS_OBJECT (key));
	g_return_if_fail (mechanism);
	g_return_if_fail (init_func);
	g_return_if_fail (complete_func);

	g_object_get (key, "handle", &args->key, NULL);
	g_return_if_fail (args->key != 0);


	memcpy (&args->mechanism, mechanism, sizeof (args->mechanism));

	args->input = input && n_input ? g_memdup (input, n_input) : NULL;
	args->n_input = n_input;

	args->init_func = init_func;
	args->complete_func = complete_func;

	args->key_object = g_object_ref (key);
	args->interaction = gck_session_get_interaction (self);

	_gck_call_async_ready_go (args, cancellable, callback, user_data);
}
