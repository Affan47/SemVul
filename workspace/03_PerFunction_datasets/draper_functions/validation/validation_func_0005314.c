free_match (gpointer data, gpointer user_data)
{
  Match *match = data;
  if (match == NULL)
    return;
  g_free (match->string);
  g_free (match);
}
