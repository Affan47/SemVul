glade_property_verify (GladeProperty * property, const GValue * value)
{
  gboolean ret = FALSE;
  GladeWidget *parent;

  parent = glade_widget_get_parent (property->priv->widget);

  if (glade_property_class_get_is_packing (property->priv->klass) && parent)
    ret =
      glade_widget_adaptor_child_verify_property (glade_widget_get_adaptor (parent),
						  glade_widget_get_object (parent),
						  glade_widget_get_object (property->priv->widget),
						  glade_property_class_id (property->priv->klass),
						  value);
  else if (!glade_property_class_get_is_packing (property->priv->klass))
    ret = glade_widget_adaptor_verify_property (glade_widget_get_adaptor (property->priv->widget),
                                                glade_widget_get_object (property->priv->widget),
                                                glade_property_class_id (property->priv->klass), value);

  return ret;
}
