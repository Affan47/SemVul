test_blob_empty (void)
{
  hb_blob_t *blob;
  unsigned int len;
  const char *data;
  char *data_writable;

  g_assert (hb_blob_is_immutable (hb_blob_get_empty ()));
  g_assert (hb_blob_get_empty () != NULL);
  g_assert (hb_blob_get_empty () == hb_blob_create (NULL, 0, HB_MEMORY_MODE_READONLY, NULL, NULL));

  blob = hb_blob_get_empty ();
  g_assert (blob == hb_blob_get_empty ());

  len = hb_blob_get_length (blob);
  g_assert_cmpint (len, ==, 0);

  data = hb_blob_get_data (blob, NULL);
  g_assert (data == NULL);

  data = hb_blob_get_data (blob, &len);
  g_assert (data == NULL);
  g_assert_cmpint (len, ==, 0);

  data_writable = hb_blob_get_data_writable (blob, NULL);
  g_assert (data_writable == NULL);

  data_writable = hb_blob_get_data_writable (blob, &len);
  g_assert (data_writable == NULL);
  g_assert_cmpint (len, ==, 0);
}
