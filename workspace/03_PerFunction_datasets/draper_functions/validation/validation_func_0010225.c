test_parse_boolean_error (void)
{
  GOptionGroup *main_group;
  GOptionEntry entries [] =
    { { "test", 0, 0, G_OPTION_ARG_NONE, &test_boolean, NULL, NULL },
      { NULL } };
  test_boolean = FALSE;
  error_test_pre_parse_fail = FALSE;
  error_test_post_parse_fail = FALSE;

  g_option_context_add_main_entries (context, entries, NULL);


  main_group = g_option_context_get_main_group (context);
  g_option_group_set_parse_hooks (main_group,
				  error_test3_pre_parse, error_test3_post_parse);


  argv = split_string ("program --test", &argc);
  cut_assert (!g_option_context_parse (context, &argc, &argv, &error));
  cut_assert (!error_test_pre_parse_fail);
  cut_assert (!error_test_post_parse_fail);

  cut_assert (!test_boolean);
}
