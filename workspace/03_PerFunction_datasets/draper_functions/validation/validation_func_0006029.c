games_scores_dialog_show (GamesScoresDialog *self)
{
  const gchar *cat;

  cat = games_scores_get_category (self->priv->scores);
  if (cat)
    games_scores_dialog_set_category (self, cat);
  games_scores_dialog_redraw (self);
}
