camel_nntp_store_has_capabilities (CamelNNTPStore *nntp_store,
                                   CamelNNTPCapabilities caps)
{
	gboolean result;

	g_return_val_if_fail (CAMEL_IS_NNTP_STORE (nntp_store), FALSE);

	g_mutex_lock (&nntp_store->priv->property_lock);

	result = ((nntp_store->priv->capabilities & caps) == caps);

	g_mutex_unlock (&nntp_store->priv->property_lock);

	return result;
}
