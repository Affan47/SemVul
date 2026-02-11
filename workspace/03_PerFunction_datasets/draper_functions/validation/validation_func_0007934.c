main (gint argc, gchar * argv[])
{
  GThread *threads[MAX_THREADS];
  gint num_threads;
  gint t;
  GstBuffer *tmp;
  GstClockTime start, end;

  gst_init (&argc, &argv);
  mutex = g_mutex_new ();

  if (argc != 3) {
    g_print ("usage: %s <num_threads> <nbbuffers>\n", argv[0]);
    exit (-1);
  }

  num_threads = atoi (argv[1]);
  nbbuffers = atoi (argv[2]);

  if (num_threads <= 0 || num_threads > MAX_THREADS) {
    g_print ("number of threads must be between 0 and %d\n", MAX_THREADS);
    exit (-2);
  }

  if (nbbuffers <= 0) {
    g_print ("number of buffers must be greater than 0\n");
    exit (-3);
  }

  g_mutex_lock (mutex);

  tmp = gst_buffer_new ();

  printf ("main(): Creating %d threads.\n", num_threads);
  for (t = 0; t < num_threads; t++) {
    GError *error = NULL;

#if !GLIB_CHECK_VERSION (2, 31, 0)
    threads[t] = g_thread_create (run_test, GINT_TO_POINTER (t), TRUE, &error);
#else
    threads[t] = g_thread_try_new ("bufferstresstest", run_test,
        GINT_TO_POINTER (t), &error);
#endif
    if (error) {
      printf ("ERROR: g_thread_create() %s\n", error->message);
      exit (-1);
    }
  }


  start = gst_util_get_timestamp ();
  g_mutex_unlock (mutex);

  for (t = 0; t < num_threads; t++) {
    if (threads[t])
      g_thread_join (threads[t]);
  }

  end = gst_util_get_timestamp ();
  g_print ("*** total %" GST_TIME_FORMAT " - average %" GST_TIME_FORMAT
      "  - Done creating %" G_GUINT64_FORMAT " buffers\n",
      GST_TIME_ARGS (end - start),
      GST_TIME_ARGS ((end - start) / (num_threads * nbbuffers)),
      num_threads * nbbuffers);


  gst_buffer_unref (tmp);

  return 0;
}
