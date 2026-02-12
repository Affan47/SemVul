static int log_kill(pid_t pid, int sig, void *userdata) {
        _cleanup_free_ char *comm = NULL;

        (void) get_process_comm(pid, &comm);


        if (comm && comm[0] == '(')
                return 0;

        log_unit_notice(userdata,
                        "Killing process " PID_FMT " (%s) with signal SIG%s.",
                        pid,
                        strna(comm),
                        signal_to_string(sig));

        return 1;
}
