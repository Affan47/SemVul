set_name (ChamplainMapSourceDesc *desc,
    const gchar *name)
{
  g_return_if_fail (CHAMPLAIN_IS_MAP_SOURCE_DESC (desc));

  ChamplainMapSourceDescPrivate *priv = desc->priv;

  g_free (priv->name);
  priv->name = g_strdup (name);

  g_object_notify (G_OBJECT (desc), "name");
}
