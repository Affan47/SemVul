gst_bin_init (GstBin * bin, GstBinClass * klass)
{
  GstBus *bus;

  bin->numchildren = 0;
  bin->children = NULL;
  bin->children_cookie = 0;
  bin->messages = NULL;
  bin->provided_clock = NULL;
  bin->clock_dirty = FALSE;


  bus = gst_bus_new ();
  bin->child_bus = bus;
  GST_DEBUG_OBJECT (bin, "using bus %" GST_PTR_FORMAT " to listen to children",
      bus);
  gst_bus_set_sync_handler (bus, (GstBusSyncHandler) bin_bus_handler, bin);

  bin->priv = GST_BIN_GET_PRIVATE (bin);
  bin->priv->asynchandling = DEFAULT_ASYNC_HANDLING;
  bin->priv->structure_cookie = 0;
  bin->priv->message_forward = DEFAULT_MESSAGE_FORWARD;
}
