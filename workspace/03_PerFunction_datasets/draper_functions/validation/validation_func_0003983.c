gth_extension_module_exec_generic_func (GthExtensionModule   *self,
					const char           *name,
					GError              **error)
{
	char *function_name;
	void (*func) (void);

	function_name = get_module_function_name (self, name);
	if (g_module_symbol (self->priv->module, function_name, (gpointer *)&func))
		func();
	else
		*error = g_error_new_literal (GTH_ERROR, GTH_ERROR_GENERIC, g_module_error ());

	g_free (function_name);

	return (*error == NULL);
}
