clutter_table_layout_get_alignment (ClutterTableLayout    *layout,
                                    ClutterActor          *actor,
                                    ClutterTableAlignment *x_align,
                                    ClutterTableAlignment *y_align)
{
  ClutterTableLayoutPrivate *priv;
  ClutterLayoutManager *manager;
  ClutterLayoutMeta *meta;

  g_return_if_fail (CLUTTER_IS_TABLE_LAYOUT (layout));
  g_return_if_fail (CLUTTER_IS_ACTOR (actor));

  priv = layout->priv;

  if (priv->container == NULL)
    {
      g_warning ("The layout of type '%s' must be associated to "
                 "a ClutterContainer before querying layout "
                 "properties",
                 G_OBJECT_TYPE_NAME (layout));
      return;
    }

  manager = CLUTTER_LAYOUT_MANAGER (layout);
  meta = clutter_layout_manager_get_child_meta (manager,
                                                priv->container,
                                                actor);
  if (meta == NULL)
    {
      g_warning ("No layout meta found for the child of type '%s' "
                 "inside the layout manager of type '%s'",
                 G_OBJECT_TYPE_NAME (actor),
                 G_OBJECT_TYPE_NAME (manager));
      return;
    }

  g_assert (CLUTTER_IS_TABLE_CHILD (meta));

  if (x_align)
    *x_align = CLUTTER_TABLE_CHILD (meta)->x_align;

  if (y_align)
    *y_align = CLUTTER_TABLE_CHILD (meta)->y_align;
}
