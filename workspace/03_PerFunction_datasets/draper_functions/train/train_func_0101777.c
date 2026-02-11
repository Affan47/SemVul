games_scores_set_category (GamesScores * self, const gchar * category)
{
  GamesScoresPrivate *priv = self->priv;

  g_return_if_fail (self != NULL);

  if (category == NULL)
    category = priv->defcat;

  g_free (priv->currentcat);
  priv->currentcat = g_strdup (category);


}
