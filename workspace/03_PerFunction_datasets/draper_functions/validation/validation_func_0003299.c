cal_backend_store_get_property (GObject *object,
                                guint property_id,
                                GValue *value,
                                GParamSpec *pspec)
{
	switch (property_id) {
		case PROP_PATH:
			g_value_set_string (
				value,
				e_cal_backend_store_get_path (
				E_CAL_BACKEND_STORE (object)));
			return;

		case PROP_TIMEZONE_CACHE:
			g_value_take_object (
				value,
				e_cal_backend_store_ref_timezone_cache (
				E_CAL_BACKEND_STORE (object)));
			return;
	}

	G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
}
