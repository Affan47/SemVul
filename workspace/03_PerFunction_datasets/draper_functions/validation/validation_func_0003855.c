clutter_score_start (ClutterScore *score)
{
  ClutterScorePrivate *priv;

  g_return_if_fail (CLUTTER_IS_SCORE (score));

  priv = score->priv;

  if (priv->is_paused)
    {
      g_hash_table_foreach (priv->running_timelines,
			    foreach_running_timeline,
			    GINT_TO_POINTER (ACTION_START));
      priv->is_paused = FALSE;
    }
  else
    {
      g_signal_emit (score, score_signals[STARTED], 0);
      g_node_children_foreach (priv->root,
                               G_TRAVERSE_ALL,
                               start_children_entries,
                               NULL);
    }
}
