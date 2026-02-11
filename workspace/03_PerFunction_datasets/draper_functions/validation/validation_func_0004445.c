__midgard_base_abstract_derived_class_get_property (GObject *object, guint prop_id,
		GValue *value, GParamSpec   *pspec)
{
	gint prop_id_local = 0;
	GType current_type = G_TYPE_FROM_INSTANCE(object);
	MgdSchemaTypeAttr *priv = G_TYPE_INSTANCE_GET_PRIVATE (object, current_type, MgdSchemaTypeAttr);
	MidgardBaseAbstract *self = (MidgardBaseAbstract *) object;
	GValue *pval;

	prop_id_local = prop_id - priv->base_index - 1;
	if ((prop_id_local >= 0)
			&& (prop_id_local < priv->num_properties)) {
		if (priv->num_properties) {
			if (priv->properties) {
				pval = &priv->properties[prop_id_local]->value;
				if (G_IS_VALUE (pval)) {
					g_value_copy(pval, value);
				}
			}
		}
	}
}
