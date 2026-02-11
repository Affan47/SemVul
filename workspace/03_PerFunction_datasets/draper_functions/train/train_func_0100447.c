__midgard_query_constraint_set_property (GObject *object, guint property_id,
		const GValue *value, GParamSpec *pspec)
{
	MidgardQueryConstraint *self = (MidgardQueryConstraint *) (object);
	GdaSqlOperatorType op_type;
	gchar *op;

	switch (property_id) {

		case MIDGARD_QUERY_CONSTRAINT_PROPERTY:
			midgard_query_constraint_set_property (self, g_value_get_object (value));
			break;

		case MIDGARD_QUERY_CONSTRAINT_OP:
			op = (gchar *)g_value_get_string (value);
       			if (__query_constraint_operator_is_valid (op, &op_type)) {
				g_free (self->priv->op);
				self->priv->op = g_strdup (op);
				self->priv->op_type = op_type;
			}
			break;

		case MIDGARD_QUERY_CONSTRAINT_HOLDER:
			if (self->priv->holder)
				g_object_unref (self->priv->holder);
			self->priv->holder = g_value_dup_object (value);
			break;

		case MIDGARD_QUERY_CONSTRAINT_STORAGE:
			midgard_query_constraint_set_storage (self, g_value_get_object (value));
			break;

  		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (self, property_id, pspec);
			break;
	}
}
