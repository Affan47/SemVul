st_theme_node_dispose (GObject *gobject)
{
  StThemeNode *node = ST_THEME_NODE (gobject);

  if (node->parent_node)
    {
      g_object_unref (node->parent_node);
      node->parent_node = NULL;
    }

  if (node->border_image)
    {
      g_object_unref (node->border_image);
      node->border_image = NULL;
    }

  if (node->icon_colors)
    {
      st_icon_colors_unref (node->icon_colors);
      node->icon_colors = NULL;
    }

  if (node->theme)
    g_signal_handlers_disconnect_by_func (node->theme,
                                          on_custom_stylesheets_changed, node);

  st_theme_node_paint_state_free (&node->cached_state);

  g_clear_object (&node->theme);

  G_OBJECT_CLASS (st_theme_node_parent_class)->dispose (gobject);
}
