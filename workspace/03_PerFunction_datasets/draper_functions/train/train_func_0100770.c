test_basic (void)
{
  DConfChangeset *changeset;
  gboolean result;
  GVariant *value;
  gint n_items;

  changeset = dconf_changeset_new ();
  dconf_changeset_ref (changeset);
  dconf_changeset_all (changeset, should_not_run, NULL);
  n_items = dconf_changeset_describe (changeset, NULL, NULL, NULL);
  g_assert_cmpint (n_items, ==, 0);
  dconf_changeset_unref (changeset);
  dconf_changeset_unref (changeset);

  changeset = dconf_changeset_new_write ("/value/a", NULL);
  result = dconf_changeset_all (changeset, is_null, NULL);
  g_assert (result);
  result = dconf_changeset_all (changeset, is_not_null, NULL);
  g_assert (!result);

  result = dconf_changeset_get (changeset, "/value/a", &value);
  g_assert (result);
  g_assert (value == NULL);

  result = dconf_changeset_get (changeset, "/value/b", &value);
  g_assert (!result);

  dconf_changeset_set (changeset, "/value/b", g_variant_new_int32 (123));
  result = dconf_changeset_all (changeset, is_null, NULL);
  g_assert (!result);
  result = dconf_changeset_all (changeset, is_not_null, NULL);
  g_assert (!result);

  result = dconf_changeset_get (changeset, "/value/a", &value);
  g_assert (result);
  g_assert (value == NULL);

  result = dconf_changeset_get (changeset, "/value/b", &value);
  g_assert (result);
  g_assert_cmpint (g_variant_get_int32 (value), ==, 123);
  g_variant_unref (value);

  dconf_changeset_set (changeset, "/value/a", g_variant_new_string ("a string"));
  result = dconf_changeset_all (changeset, is_null, NULL);
  g_assert (!result);
  result = dconf_changeset_all (changeset, is_not_null, NULL);
  g_assert (result);

  result = dconf_changeset_get (changeset, "/value/a", &value);
  g_assert (result);
  g_assert_cmpstr (g_variant_get_string (value, NULL), ==, "a string");
  g_variant_unref (value);

  result = dconf_changeset_get (changeset, "/value/b", &value);
  g_assert (result);
  g_assert_cmpint (g_variant_get_int32 (value), ==, 123);
  g_variant_unref (value);

  dconf_changeset_unref (changeset);
}
