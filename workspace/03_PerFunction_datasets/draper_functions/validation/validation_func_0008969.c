im_hangul_finalize (void)
{
  GSList *item;


  if (snooper_handler_id > 0) {
    gtk_key_snooper_remove(snooper_handler_id);
    snooper_handler_id = 0;
  }


  for (item = toplevels; item != NULL; item = g_slist_next(item)) {
    toplevel_delete((Toplevel*)item->data);
  }
  g_slist_free(toplevels);
  toplevels = NULL;

  im_hangul_accel_list_free(hanja_keys);
  hanja_keys = NULL;

  im_hangul_accel_list_free(hangul_keys);
  hangul_keys = NULL;
}
