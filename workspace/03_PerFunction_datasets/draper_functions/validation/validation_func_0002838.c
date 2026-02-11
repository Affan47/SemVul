almanah_entry_get_property (GObject *object, guint property_id, GValue *value, GParamSpec *pspec)
{
	AlmanahEntryPrivate *priv = ALMANAH_ENTRY (object)->priv;

	switch (property_id) {
		case PROP_DAY:
			g_value_set_uint (value, g_date_get_day (&(priv->date)));
			break;
		case PROP_MONTH:
			g_value_set_uint (value, g_date_get_month (&(priv->date)));
			break;
		case PROP_YEAR:
			g_value_set_uint (value, g_date_get_year (&(priv->date)));
			break;
		case PROP_IS_IMPORTANT:
			g_value_set_boolean (value, priv->is_important);
			break;
		case PROP_LAST_EDITED_DAY:
			g_value_set_uint (value, g_date_get_day (&(priv->last_edited)));
			break;
		case PROP_LAST_EDITED_MONTH:
			g_value_set_uint (value, g_date_get_month (&(priv->last_edited)));
			break;
		case PROP_LAST_EDITED_YEAR:
			g_value_set_uint (value, g_date_get_year (&(priv->last_edited)));
			break;
		default:

			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
	}
}
