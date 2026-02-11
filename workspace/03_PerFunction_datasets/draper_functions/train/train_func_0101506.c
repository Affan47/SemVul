_vala_caribou_key_model_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	CaribouKeyModel * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (object, CARIBOU_TYPE_KEY_MODEL, CaribouKeyModel);
	switch (property_id) {
		case CARIBOU_KEY_MODEL_ALIGN:
		g_value_set_string (value, caribou_key_model_get_align (self));
		break;
		case CARIBOU_KEY_MODEL_WIDTH:
		g_value_set_double (value, caribou_key_model_get_width (self));
		break;
		case CARIBOU_KEY_MODEL_TOGGLE:
		g_value_set_string (value, caribou_key_model_get_toggle (self));
		break;
		case CARIBOU_KEY_MODEL_REPEATABLE:
		g_value_set_boolean (value, caribou_key_model_get_repeatable (self));
		break;
		case CARIBOU_KEY_MODEL_IS_MODIFIER:
		g_value_set_boolean (value, caribou_key_model_get_is_modifier (self));
		break;
		case CARIBOU_KEY_MODEL_SHOW_SUBKEYS:
		g_value_set_boolean (value, caribou_key_model_get_show_subkeys (self));
		break;
		case CARIBOU_KEY_MODEL_NAME:
		g_value_set_string (value, caribou_key_model_get_name (self));
		break;
		case CARIBOU_KEY_MODEL_KEYVAL:
		g_value_set_uint (value, caribou_key_model_get_keyval (self));
		break;
		case CARIBOU_KEY_MODEL_TEXT:
		g_value_set_string (value, caribou_key_model_get_text (self));
		break;
		case CARIBOU_KEY_MODEL_LABEL:
		g_value_set_string (value, caribou_key_model_get_label (self));
		break;
		case CARIBOU_KEY_MODEL_SCAN_STEPPING:
		g_value_set_boolean (value, caribou_iscannable_item_get_scan_stepping ((CaribouIScannableItem*) self));
		break;
		case CARIBOU_KEY_MODEL_SCAN_SELECTED:
		g_value_set_boolean (value, caribou_iscannable_item_get_scan_selected ((CaribouIScannableItem*) self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}
