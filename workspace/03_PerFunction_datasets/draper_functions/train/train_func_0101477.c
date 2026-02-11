test_conform_simple_fixture_setup (TestConformSimpleFixture *fixture,
				   gconstpointer data)
{
  const TestConformSharedState *shared_state = data;
  static int counter = 0;

  if (counter != 0)
    g_critical ("We don't support running more than one test at a time\n"
                "in a single test run due to the state leakage that often\n"
                "causes subsequent tests to fail.\n"
                "\n"
                "If you want to run all the tests you should run\n"
                "$ make test-report");
  counter++;

#ifdef CLUTTER_WINDOWING_X11
  if (clutter_check_windowing_backend (CLUTTER_WINDOWING_X11))
    {

      const gchar *display = g_getenv ("DISPLAY");
      if (!display || *display == '\0')
        {
          g_print ("No DISPLAY found. Unable to run the conformance "
                   "test suite without a display.\n");

          exit (EXIT_SUCCESS);
        }


      clutter_x11_enable_xinput ();
    }
#endif

  g_assert (clutter_init (shared_state->argc_addr, shared_state->argv_addr)
            == CLUTTER_INIT_SUCCESS);

#ifdef CLUTTER_WINDOWING_X11


  if (clutter_check_windowing_backend (CLUTTER_WINDOWING_X11))
    XSynchronize (clutter_x11_get_default_display(), TRUE);
#endif
}
