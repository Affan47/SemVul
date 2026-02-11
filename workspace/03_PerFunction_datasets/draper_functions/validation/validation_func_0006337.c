sasl_map_done()
{
	int ret = 0;
	sasl_map_private *priv = sasl_map_get_global_priv();
	sasl_map_data *dp = NULL;


	if (!priv || !priv->lock || !priv->map_data_list) {
		return 0;
	}


	slapi_rwlock_wrlock(priv->lock);
	dp = priv->map_data_list;
	while (dp) {
		sasl_map_data *dp_next = dp->next;
		sasl_map_free_data(&dp);
		dp = dp_next;
	}
	slapi_rwlock_unlock(priv->lock);


	sasl_map_free_private(&priv);
	return ret;
}
