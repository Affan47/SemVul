gdata_picasaweb_service_get_user_finish (GDataPicasaWebService *self, GAsyncResult *async_result, GError **error)
{
	GSimpleAsyncResult *result;

	g_return_val_if_fail (GDATA_IS_PICASAWEB_SERVICE (self), NULL);
	g_return_val_if_fail (G_IS_ASYNC_RESULT (async_result), NULL);
	g_return_val_if_fail (error == NULL || *error == NULL, NULL);

	g_return_val_if_fail (g_simple_async_result_is_valid (async_result, G_OBJECT (self), gdata_picasaweb_service_get_user_async) == TRUE, NULL);

	result = G_SIMPLE_ASYNC_RESULT (async_result);

	if (g_simple_async_result_propagate_error (result, error) == TRUE) {
		return NULL;
	}

	return g_simple_async_result_get_op_res_gpointer (result);
}
