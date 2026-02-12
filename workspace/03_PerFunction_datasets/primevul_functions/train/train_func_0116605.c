static int enable_special_signals(Manager *m) {
        _cleanup_close_ int fd = -1;

        assert(m);


        if (reboot(RB_DISABLE_CAD) < 0 && errno != EPERM && errno != EINVAL)
                log_warning("Failed to enable ctrl-alt-del handling: %m");

        fd = open_terminal("/dev/tty0", O_RDWR|O_NOCTTY|O_CLOEXEC);
        if (fd < 0) {

                if (fd != -ENOENT)
                        log_warning("Failed to open /dev/tty0: %m");
        } else {

                if (ioctl(fd, KDSIGACCEPT, SIGWINCH) < 0)
                        log_warning("Failed to enable kbrequest handling: %m");
        }

        return 0;
}
