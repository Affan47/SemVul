source_selector_get_property (GObject *object,
                              guint property_id,
                              GValue *value,
                              GParamSpec *pspec)
{
	switch (property_id) {
		case PROP_EXTENSION_NAME:
			g_value_set_string (
				value,
				e_source_selector_get_extension_name (
				E_SOURCE_SELECTOR (object)));
			return;

		case PROP_PRIMARY_SELECTION:
			g_value_take_object (
				value,
				e_source_selector_ref_primary_selection (
				E_SOURCE_SELECTOR (object)));
			return;

		case PROP_REGISTRY:
			g_value_set_object (
				value,
				e_source_selector_get_registry (
				E_SOURCE_SELECTOR (object)));
			return;

		case PROP_SHOW_COLORS:
			g_value_set_boolean (
				value,
				e_source_selector_get_show_colors (
				E_SOURCE_SELECTOR (object)));
			return;

		case PROP_SHOW_TOGGLES:
			g_value_set_boolean (
				value,
				e_source_selector_get_show_toggles (
				E_SOURCE_SELECTOR (object)));
			return;
	}

	G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
}
