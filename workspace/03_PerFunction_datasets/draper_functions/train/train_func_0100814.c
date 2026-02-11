st_widget_accessible_get_name (AtkObject *obj)
{
  const gchar* name = NULL;

  g_return_val_if_fail (ST_IS_WIDGET_ACCESSIBLE (obj), NULL);

  name = ATK_OBJECT_CLASS (st_widget_accessible_parent_class)->get_name (obj);
  if (name == NULL)
    {
      StWidget *widget = NULL;

      widget = ST_WIDGET (atk_gobject_accessible_get_object (ATK_GOBJECT_ACCESSIBLE (obj)));

      if (widget == NULL)
        name = NULL;
      else
        name = widget->priv->accessible_name;
    }

  return name;
}
