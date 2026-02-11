_wnck_application_destroy (WnckApplication *application)
{
  g_return_if_fail (wnck_application_get (application->priv->xwindow) == application);

  g_hash_table_remove (app_hash, &application->priv->xwindow);

  g_return_if_fail (wnck_application_get (application->priv->xwindow) == NULL);


  g_object_unref (G_OBJECT (application));
}
