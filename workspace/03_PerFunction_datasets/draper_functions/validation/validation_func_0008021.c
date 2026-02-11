totem_cmml_context_set_callback (TotemCmmlContext	*context,
				 TotemCmmlCallback	cb,
				 gpointer		user_data)
{
	g_return_if_fail (context != NULL);

	context->callback = cb;
	context->user_data = user_data;
}
