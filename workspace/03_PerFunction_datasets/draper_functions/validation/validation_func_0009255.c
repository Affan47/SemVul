gst_wavenc_is_cue_id_unique (guint32 id, GList * list)
{
  GstWavEncCue *cue;

  while (list) {
    cue = list->data;
    if (cue->id == id)
      return FALSE;
    list = g_list_next (list);
  }

  return TRUE;
}
