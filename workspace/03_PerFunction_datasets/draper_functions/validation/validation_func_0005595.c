main(int argc, char **argv) {
	isc_result_t result;

	ISC_LIST_INIT(lookup_list);
	ISC_LIST_INIT(server_list);
	ISC_LIST_INIT(search_list);

	debug("main()");
	preparse_args(argc, argv);
	progname = argv[0];
	result = isc_app_start();
	check_result(result, "isc_app_start");
	setup_libs();
	parse_args(ISC_FALSE, ISC_FALSE, argc, argv);
	setup_system();
	if (domainopt[0] != '\0') {
		set_search_domain(domainopt);
		usesearch = ISC_TRUE;
	}
	result = isc_app_onrun(mctx, global_task, onrun_callback, NULL);
	check_result(result, "isc_app_onrun");
	isc_app_run();
	destroy_lookup(default_lookup);
	if (batchname != NULL) {
		if (batchfp != stdin)
			fclose(batchfp);
		batchname = NULL;
	}
#ifdef DIG_SIGCHASE
	clean_trustedkey();
#endif
	cancel_all();
	destroy_libs();
	isc_app_finish();
	return (exitcode);
}
