exit_tasks(PROJECT* proj) {
    if (log_flags.task_debug) {
        msg_printf(NULL, MSG_INFO, "[task_debug] requesting tasks to exit");
    }
    request_tasks_exit(proj);


    if (wait_for_exit(MAX_EXIT_TIME, proj)) {
        if (log_flags.task_debug) {
            msg_printf(NULL, MSG_INFO,
                "[task_debug] all tasks haven't exited after %d sec; killing them",
                MAX_EXIT_TIME
            );
        }
        kill_tasks(proj);
        if (wait_for_exit(5, proj)) {
            if (log_flags.task_debug) {
                msg_printf(NULL, MSG_INFO,
                    "[task_debug] tasks still not exited after 5 secs; giving up"
                );
            }
        } else {
            if (log_flags.task_debug) {
                msg_printf(NULL, MSG_INFO, "[task_debug] all tasks exited");
            }
        }
    } else {
        if (log_flags.task_debug) {
            msg_printf(NULL, MSG_INFO, "[task_debug] all tasks exited");
        }
    }


    get_msgs();

    gstate.request_schedule_cpus("exit_tasks");
    return 0;
}
