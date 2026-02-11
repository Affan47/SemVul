__transform_value(MidgardCoreQueryConstraint *self)
{
	GValue *value = self->priv->value;
	GValue *target = g_new0(GValue, 1);
	g_value_init(target, G_PARAM_SPEC_VALUE_TYPE(self->priv->pspec));
	gboolean value_unset = TRUE;


	if (!g_param_value_convert((GParamSpec *)self->priv->pspec, value, target, FALSE)) {

		value_unset = FALSE;

		if (G_VALUE_HOLDS_STRING(value) && G_VALUE_HOLDS_UINT(target)) {

			guint uvalue = strtoul(g_value_get_string(value), NULL, 0);
			g_value_set_uint(target, uvalue);
			value_unset = TRUE;

		} else if (G_VALUE_HOLDS_STRING(value) && G_VALUE_HOLDS_INT(target)) {

			gint ivalue = strtoul(g_value_get_string(value), NULL, 0);
			g_value_set_int(target, ivalue);
			value_unset = TRUE;

		} else {

			if (value && target) {

				g_warning("Invalid value conversion from %s to %s",
						G_VALUE_TYPE_NAME(value),
						G_VALUE_TYPE_NAME(target));
			}
		}
	}

	if(value_unset) {

		g_value_unset(value);
		g_free(value);

		self->priv->value = target;

		return;
	}

	g_value_unset(target);
	g_free(target);

	return;
}
