gda_data_proxy_append_row (GdaDataModel *model, G_GNUC_UNUSED GError **error)
{
	GdaDataProxy *proxy;
	gint i;
	g_return_val_if_fail (GDA_IS_DATA_PROXY (model), -1);
	proxy = GDA_DATA_PROXY (model);
	g_return_val_if_fail (proxy->priv, -1);

	gda_mutex_lock (proxy->priv->mutex);
	i = gda_data_proxy_append (proxy);
	gda_mutex_unlock (proxy->priv->mutex);
	return i;
}
