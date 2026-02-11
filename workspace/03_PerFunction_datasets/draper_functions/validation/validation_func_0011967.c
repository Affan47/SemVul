gtr_view_set_search_text (GtrView * view, const gchar * text, guint flags)
{
  gchar *converted_text;

  g_return_if_fail (GTR_IS_VIEW (view));
  g_return_if_fail ((text == NULL) || (view->priv->search_text != text));
  g_return_if_fail ((text == NULL) || g_utf8_validate (text, -1, NULL));


  if (text != NULL)
    {
      if (*text != '\0')
        {
          converted_text = gtr_utils_unescape_search_text (text);
        }
      else
        {
          converted_text = g_strdup ("");
        }

      g_free (view->priv->search_text);

      view->priv->search_text = converted_text;


    }

  if (!GTR_SEARCH_IS_DONT_SET_FLAGS (flags))
    {


      view->priv->search_flags = flags;

    }


}
