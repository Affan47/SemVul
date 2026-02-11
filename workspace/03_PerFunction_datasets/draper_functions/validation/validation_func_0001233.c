gkm_object_get_property (GObject *obj, guint prop_id, GValue *value,
                           GParamSpec *pspec)
{
	GkmObject *self = GKM_OBJECT (obj);

	switch (prop_id) {
	case PROP_HANDLE:
		g_value_set_ulong (value, gkm_object_get_handle (self));
		break;
	case PROP_MODULE:
		g_return_if_fail (GKM_IS_MODULE (self->pv->module));
		g_value_set_object (value, gkm_object_get_module (self));
		break;
	case PROP_MANAGER:
		g_value_set_object (value, gkm_object_get_manager (self));
		break;
	case PROP_STORE:
		g_value_set_object (value, self->pv->store);
		break;
	case PROP_UNIQUE:
		g_value_set_string (value, gkm_object_get_unique (self));
		break;
	case PROP_TRANSIENT:
		g_value_set_boolean (value, gkm_object_is_transient (self));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (obj, prop_id, pspec);
		break;
	}
}
