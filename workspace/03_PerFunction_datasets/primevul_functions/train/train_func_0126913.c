static void setup_chroot(struct lo_data *lo)
{
    lo->proc_self_fd = open("/proc/self/fd", O_PATH);
    if (lo->proc_self_fd == -1) {
        fuse_log(FUSE_LOG_ERR, "open(\"/proc/self/fd\", O_PATH): %m\n");
        exit(1);
    }


    if (chroot(lo->source) != 0) {
        fuse_log(FUSE_LOG_ERR, "chroot(\"%s\"): %m\n", lo->source);
        exit(1);
    }


    if (chdir("/") != 0) {
        fuse_log(FUSE_LOG_ERR, "chdir(\"/\"): %m\n");
        exit(1);
    }
}
