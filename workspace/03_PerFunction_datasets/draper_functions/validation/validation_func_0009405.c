unsuspend(int reason) {
    if (!app_client_shm.shm) return 0;
    if (task_state() != PROCESS_SUSPENDED) {
        msg_printf(result->project, MSG_INFO,
            "Internal error: expected process %s to be suspended", result->name
        );
    }
    if (log_flags.cpu_sched && reason != SUSPEND_REASON_CPU_THROTTLE) {
        msg_printf(result->project, MSG_INFO,
            "[cpu_sched] Resuming %s", result->name
        );
    }
    int n = process_control_queue.msg_queue_purge("<suspend/>");
    if (n == 0) {
        process_control_queue.msg_queue_send(
            "<resume/>",
            app_client_shm.shm->process_control_request
        );
    }
    set_task_state(PROCESS_EXECUTING, "unsuspend");
    return 0;
}
