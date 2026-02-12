static int load_capng(void)
{
    if (!cap_loaded) {
        pthread_mutex_lock(&cap.mutex);
        capng_restore_state(&cap.saved);


        cap.saved = capng_save_state();
        if (!cap.saved) {
            pthread_mutex_unlock(&cap.mutex);
            fuse_log(FUSE_LOG_ERR, "capng_save_state (thread)\n");
            return -EINVAL;
        }
        pthread_mutex_unlock(&cap.mutex);


        capng_setpid(syscall(SYS_gettid));
        cap_loaded = true;
    }
    return 0;
}
