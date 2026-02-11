cell_renderer_color_get_property (GObject *object,
                                  guint property_id,
                                  GValue *value,
                                  GParamSpec *pspec)
{
	ECellRendererColorPrivate *priv;

	priv = E_CELL_RENDERER_COLOR_GET_PRIVATE (object);

	switch (property_id) {
		case PROP_COLOR:
			g_value_set_boxed (value, priv->color);
			return;
	}

	G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
}
