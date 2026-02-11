gst_ghost_pad_setcaps_default (GstPad * pad, GstCaps * caps)
{
  g_return_val_if_fail (GST_IS_GHOST_PAD (pad), FALSE);
  g_return_val_if_fail (caps == NULL || GST_IS_CAPS (caps), FALSE);

  if (GST_PAD_DIRECTION (pad) == GST_PAD_SRC)
    return TRUE;

  return gst_proxy_pad_setcaps_default (pad, caps);
}
