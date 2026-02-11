mpegpsmux_finalize (GObject * object)
{
  MpegPsMux *mux = GST_MPEG_PSMUX (object);

  if (mux->collect) {
    gst_object_unref (mux->collect);
    mux->collect = NULL;
  }
  if (mux->psmux) {
    psmux_free (mux->psmux);
    mux->psmux = NULL;
  }

  if (mux->gop_list != NULL) {
    gst_buffer_list_unref (mux->gop_list);
    mux->gop_list = NULL;
  }

  G_OBJECT_CLASS (mpegpsmux_parent_class)->finalize (object);
}
