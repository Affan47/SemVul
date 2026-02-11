create_profiler (const char *filename, GPtrArray *filters)
{
	MonoProfiler *prof;
	char *nf;
	int force_delete = 0;
	prof = (MonoProfiler *)calloc (1, sizeof (MonoProfiler));

	prof->command_port = command_port;
	if (filename && *filename == '-') {
		force_delete = 1;
		filename++;
	}
	if (!filename) {
		if (do_report)
			filename = "|mprof-report -";
		else
			filename = "output.mlpd";
		nf = (char*)filename;
	} else {
		nf = new_filename (filename);
		if (do_report) {
			int s = strlen (nf) + 32;
			char *p = (char *)malloc (s);
			snprintf (p, s, "|mprof-report '--out=%s' -", nf);
			free (nf);
			nf = p;
		}
	}
	if (*nf == '|') {
		prof->file = popen (nf + 1, "w");
		prof->pipe_output = 1;
	} else if (*nf == '#') {
		int fd = strtol (nf + 1, NULL, 10);
		prof->file = fdopen (fd, "a");
	} else {
		if (force_delete)
			unlink (nf);
		prof->file = fopen (nf, "wb");
	}
	if (!prof->file) {
		fprintf (stderr, "Cannot create profiler output: %s\n", nf);
		exit (1);
	}
#if defined (HAVE_SYS_ZLIB)
	if (use_zip)
		prof->gzfile = gzdopen (fileno (prof->file), "wb");
#endif
#if USE_PERF_EVENTS
	if (sample_type && !do_mono_sample)
		need_helper_thread = setup_perf_event ();
	if (!perf_data) {

		do_mono_sample = 1;
	}
#endif
	if (do_mono_sample) {
		prof->stat_buffers = create_stat_buffer ();
		need_helper_thread = 1;
	}
	if (do_counters && !need_helper_thread) {
		need_helper_thread = 1;
	}

	prof->sorted_sample_events = g_ptr_array_sized_new (BUFFER_SIZE / SAMPLE_EVENT_SIZE_IN_SLOTS (0));

#ifdef DISABLE_HELPER_THREAD
	if (hs_mode_ondemand)
		fprintf (stderr, "Ondemand heapshot unavailable on this arch.\n");

	if (do_coverage)
		fprintf (stderr, "Coverage unavailable on this arch.\n");

#endif

	mono_lock_free_queue_init (&prof->writer_queue);
	mono_os_mutex_init (&prof->method_table_mutex);
	prof->method_table = mono_conc_hashtable_new (NULL, NULL);

	if (do_coverage)
		coverage_init (prof);
	prof->coverage_filters = filters;

	prof->startup_time = current_time ();
	return prof;
}
