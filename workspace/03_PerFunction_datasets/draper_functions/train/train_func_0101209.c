create_random_key (void)
{
  GString *key;
  gint i, n;

  key = g_string_new (NULL);
  n = g_test_rand_int_range (1, 5);
  for (i = 0; i < n; i++)
    {
      gint j;

      g_string_append_c (key, '/');
      for (j = 0; j < 5; j++)
        g_string_append_c (key, g_test_rand_int_range ('a', 'z' + 1));
    }

  return g_string_free (key, FALSE);
}
