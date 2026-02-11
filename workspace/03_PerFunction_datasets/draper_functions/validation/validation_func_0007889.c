search_text_notify_cb (TpawLiveSearch *search,
    GParamSpec *pspec,
    TpawIrcNetworkChooserDialog *self)
{
  GtkTreeIter filter_iter;
  gboolean sensitive = FALSE;

  gtk_tree_model_filter_refilter (self->priv->filter);


  if (gtk_tree_model_get_iter_first (GTK_TREE_MODEL (self->priv->filter),
        &filter_iter))
    {
      const gchar *text;

      text = tpaw_live_search_get_text (
          TPAW_LIVE_SEARCH (self->priv->search));
      if (!TPAW_STR_EMPTY (text))
        {

          select_iter (self, &filter_iter, TRUE);
        }
      else
        {

          GtkTreeSelection *selection;

          selection = gtk_tree_view_get_selection (
              GTK_TREE_VIEW (self->priv->treeview));

          if (gtk_tree_selection_get_selected (selection, NULL,
                &filter_iter))
            scroll_to_iter (self, &filter_iter);
        }

      sensitive = TRUE;
    }

  gtk_widget_set_sensitive (self->priv->select_button, sensitive);
}
