set_now() {
    double x = dtime();


    clock_change = false;
    if (x < (now-60)) {
        clock_change = true;
        msg_printf(NULL, MSG_INFO,
            "New system time (%.0f) < old system time (%.0f); clearing timeouts",
            x, now
        );
        clear_absolute_times();
    }

#ifdef _WIN32


    if (os_requested_suspend) {
        if (x > now+10) {
            msg_printf(0, MSG_INFO, "Resuming after OS suspension");
            os_requested_suspend = false;
        } else if (x > os_requested_suspend_time + 300) {
            msg_printf(0, MSG_INFO, "Resuming after OS suspension");
            os_requested_suspend = false;
        }
    }
#endif
    now = x;
}
