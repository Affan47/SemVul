int unit_pid_attachable(Unit *u, pid_t pid, sd_bus_error *error) {
        int r;

        assert(u);


        if (!pid_is_valid(pid))
                return sd_bus_error_setf(error, SD_BUS_ERROR_INVALID_ARGS, "Process identifier " PID_FMT " is not valid.", pid);


        if (pid == 1 || pid == getpid_cached())
                return sd_bus_error_setf(error, SD_BUS_ERROR_INVALID_ARGS, "Process " PID_FMT " is a manager process, refusing.", pid);


        r = is_kernel_thread(pid);
        if (r == -ESRCH)
                return sd_bus_error_setf(error, SD_BUS_ERROR_UNIX_PROCESS_ID_UNKNOWN, "Process with ID " PID_FMT " does not exist.", pid);
        if (r < 0)
                return sd_bus_error_set_errnof(error, r, "Failed to determine whether process " PID_FMT " is a kernel thread: %m", pid);
        if (r > 0)
                return sd_bus_error_setf(error, SD_BUS_ERROR_INVALID_ARGS, "Process " PID_FMT " is a kernel thread, refusing.", pid);

        return 0;
}
