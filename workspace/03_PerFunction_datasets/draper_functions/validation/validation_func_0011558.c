gdict_defbox_set_show_find (GdictDefbox *defbox,
			    gboolean     show_find)
{
  GdictDefboxPrivate *priv;

  g_return_if_fail (GDICT_IS_DEFBOX (defbox));

  priv = defbox->priv;

  if (priv->show_find == show_find)
    return;

  priv->show_find = show_find;
  if (priv->show_find)
    {
      gtk_widget_show_all (priv->find_pane);
      gtk_widget_grab_focus (priv->find_entry);

      if (!priv->hide_timeout)
        priv->hide_timeout = g_timeout_add (5000, hide_find_pane, defbox);
    }
  else
    {
      gtk_widget_hide (priv->find_pane);

      if (priv->hide_timeout)
        {
          g_source_remove (priv->hide_timeout);
          priv->hide_timeout = 0;
        }
    }
}
