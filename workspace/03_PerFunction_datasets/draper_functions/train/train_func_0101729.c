get_address (GcIfaceAddress   *iface,
             int              *timestamp,
             GHashTable      **address,
             GeoclueAccuracy **accuracy,
             GError          **error)
{
	GcMasterClient *client = GC_MASTER_CLIENT (iface);
	GcMasterClientPrivate *priv = GET_PRIVATE (client);

	if (priv->address_provider == NULL) {
		if (error) {
			*error = g_error_new (GEOCLUE_ERROR,
			                      GEOCLUE_ERROR_NOT_AVAILABLE,
			                      "Geoclue master client has no usable Address providers");
		}
		return FALSE;
	}

	return gc_master_provider_get_address
		(priv->address_provider,
		 timestamp,
		 address,
		 accuracy,
		 error);
}
