boinc_init_options_general(BOINC_OPTIONS& opt) {
    int retval;
    char buf[256];
    options = opt;

    if (!diagnostics_is_initialized()) {
        retval = boinc_init_diagnostics(BOINC_DIAG_DEFAULTS);
        if (retval) return retval;
    }

    boinc_status.no_heartbeat = false;
    boinc_status.suspended = false;
    boinc_status.quit_request = false;
    boinc_status.abort_request = false;

    if (options.main_program) {


        retval = file_lock.lock(LOCKFILE);
        if (retval) {


            fprintf(stderr, "%s Can't acquire lockfile (%d) - waiting %ds\n",
                boinc_msg_prefix(buf, sizeof(buf)),
                retval, LOCKFILE_TIMEOUT_PERIOD
            );
            boinc_sleep(LOCKFILE_TIMEOUT_PERIOD);
            retval = file_lock.lock(LOCKFILE);
        }
        if (retval) {
            fprintf(stderr, "%s Can't acquire lockfile (%d) - exiting\n",
                boinc_msg_prefix(buf, sizeof(buf)),
                retval
            );
#ifdef _WIN32
            char buf2[256];
            windows_format_error_string(GetLastError(), buf2, 256);
            fprintf(stderr, "%s Error: %s\n", boinc_msg_prefix(buf, sizeof(buf)), buf2);
#endif


            boinc_temporary_exit(600, "Waiting to acquire lock");
        }
    }

    retval = boinc_parse_init_data_file();
    if (retval) {
        standalone = true;
    } else {
        retval = setup_shared_mem();
        if (retval) {
            fprintf(stderr,
                "%s Can't set up shared mem: %d. Will run in standalone mode.\n",
                boinc_msg_prefix(buf, sizeof(buf)), retval
            );
            standalone = true;
        }
    }


    initial_wu_cpu_time = aid.wu_cpu_time;

    fraction_done = -1;
    time_until_checkpoint = min_checkpoint_period();
    last_checkpoint_cpu_time = aid.wu_cpu_time;
    last_wu_cpu_time = aid.wu_cpu_time;

    if (standalone) {
        options.check_heartbeat = false;
    }
    heartbeat_giveup_count = interrupt_count + HEARTBEAT_GIVEUP_COUNT;

    init_mutex();

    return 0;
}
