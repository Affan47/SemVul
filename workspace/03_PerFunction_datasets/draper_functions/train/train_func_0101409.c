sparql_connection_ready_cb (GObject *object,
                            GAsyncResult *res,
                            gpointer user_data)
{
  GError *error = NULL;
  GomMiner *self = user_data;

  self->priv->connection = tracker_sparql_connection_get_finish (res, &error);

  if (error != NULL)
    {
      gom_miner_complete_error (self, error);
      return;
    }

  gom_miner_refresh_db_real (self);
}
