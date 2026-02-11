gst_base_transform_set_passthrough (GstBaseTransform * trans,
    gboolean passthrough)
{
  GstBaseTransformClass *bclass;

  g_return_if_fail (GST_IS_BASE_TRANSFORM (trans));

  bclass = GST_BASE_TRANSFORM_GET_CLASS (trans);

  GST_OBJECT_LOCK (trans);
  if (passthrough == FALSE) {
    if (bclass->transform_ip || bclass->transform)
      trans->priv->passthrough = FALSE;
  } else {
    trans->priv->passthrough = TRUE;
  }

  GST_DEBUG_OBJECT (trans, "set passthrough %d", trans->priv->passthrough);
  GST_OBJECT_UNLOCK (trans);
}
