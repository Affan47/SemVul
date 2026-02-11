test_buffer_empty (void)
{
  hb_buffer_t *b = hb_buffer_get_empty ();

  g_assert (hb_buffer_get_empty ());
  g_assert (hb_buffer_get_empty () == b);

  g_assert (!hb_buffer_allocation_successful (b));

  test_empty (b);

  hb_buffer_add_utf32 (b, utf32, G_N_ELEMENTS (utf32), 1, G_N_ELEMENTS (utf32) - 2);

  test_empty (b);

  hb_buffer_reverse (b);
  hb_buffer_reverse_clusters (b);

  g_assert (!hb_buffer_set_length (b, 10));

  test_empty (b);

  g_assert (hb_buffer_set_length (b, 0));

  test_empty (b);

  g_assert (!hb_buffer_allocation_successful (b));

  hb_buffer_reset (b);

  test_empty (b);

  g_assert (!hb_buffer_allocation_successful (b));
}
