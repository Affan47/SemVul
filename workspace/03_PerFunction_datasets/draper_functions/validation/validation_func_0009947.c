xmms_normalize_init (xmms_xform_t *xform)
{
	xmms_config_property_t *cfgv;
	xmms_normalize_data_t *data;
	int i;

	g_return_val_if_fail (xform, FALSE);

	data = g_new0 (xmms_normalize_data_t, 1);

	for (i = 0; i < G_N_ELEMENTS (config_params); i++) {
		cfgv = xmms_xform_config_lookup (xform, config_params[i].key);
		xmms_config_property_callback_set (cfgv,
		                                   xmms_normalize_config_changed,
		                                   data);

		xmms_normalize_config_changed (XMMS_OBJECT (cfgv), NULL, data);
	}

	xmms_xform_outdata_type_copy (xform);

	data->dirty = FALSE;

	data->compress = compress_new (data->use_anticlip,
	                               data->target,
	                               data->max_gain,
	                               data->smooth,
	                               data->buckets);

	xmms_xform_private_data_set (xform, data);

	return TRUE;
}
