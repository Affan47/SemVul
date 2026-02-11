ges_title_clip_set_font_desc (GESTitleClip * self, const gchar * font_desc)
{
  GSList *tmp;

  GST_DEBUG_OBJECT (self, "font_desc:%s", font_desc);

  if (self->priv->font_desc)
    g_free (self->priv->font_desc);

  self->priv->font_desc = g_strdup (font_desc);

  for (tmp = self->priv->track_titles; tmp; tmp = tmp->next) {
    ges_title_source_set_font_desc (GES_TITLE_SOURCE (tmp->data),
        self->priv->font_desc);
  }
}
