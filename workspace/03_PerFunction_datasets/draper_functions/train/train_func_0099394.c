update_wmclass (MatewnckWindow *window)
{
  if (!window->priv->need_update_wmclass)
    return;

  window->priv->need_update_wmclass = FALSE;

  g_free (window->priv->res_class);
  g_free (window->priv->res_name);

  window->priv->res_class = NULL;
  window->priv->res_name = NULL;

  _matewnck_get_wmclass (window->priv->xwindow,
                     &window->priv->res_class,
                     &window->priv->res_name);
}
