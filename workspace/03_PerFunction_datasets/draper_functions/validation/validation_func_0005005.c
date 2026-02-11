g_flickr_tags_getHotList (GFlickr *f,
                          gint count,
                          GFlickrListCb callback,
                          gpointer user_data)
{
  g_return_if_fail (G_IS_FLICKR (f));

  gchar *params[2];

  params[0] = g_strdup_printf ("count=%d", count);
  params[1] = g_strdup_printf ("method=%s", FLICKR_TAGS_GETHOTLIST_METHOD);

  gchar *request = create_url (f, params, 2);

  free_params (params, 2);

  GFlickrData *gfd = g_slice_new (GFlickrData);
  gfd->flickr = g_object_ref (f);
  gfd->parse_xml = process_taglist_result;
  gfd->list_cb = callback;
  gfd->user_data = user_data;

  read_url_async (f, request, gfd);
  g_free (request);
}
