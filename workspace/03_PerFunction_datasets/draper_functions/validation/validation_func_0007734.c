gst_nuv_demux_finalize (GObject * object)
{
  GstNuvDemux *nuv = GST_NUV_DEMUX (object);

  if (nuv->mpeg_buffer != NULL) {
    gst_buffer_unref (nuv->mpeg_buffer);
  }

  gst_nuv_demux_destoy_src_pad (nuv);
  gst_nuv_demux_reset (nuv);
  if (nuv->adapter != NULL) {
    g_object_unref (nuv->adapter);
    nuv->adapter = NULL;
  }
  G_OBJECT_CLASS (parent_class)->finalize (object);
}
