static void setup_capabilities(char *modcaps_in)
{
    char *modcaps = modcaps_in;
    pthread_mutex_lock(&cap.mutex);
    capng_restore_state(&cap.saved);


    capng_setpid(syscall(SYS_gettid));
    capng_clear(CAPNG_SELECT_BOTH);
    if (capng_updatev(CAPNG_ADD, CAPNG_PERMITTED | CAPNG_EFFECTIVE,
            CAP_CHOWN,
            CAP_DAC_OVERRIDE,
            CAP_FOWNER,
            CAP_FSETID,
            CAP_SETGID,
            CAP_SETUID,
            CAP_MKNOD,
            CAP_SETFCAP,
            -1)) {
        fuse_log(FUSE_LOG_ERR, "%s: capng_updatev failed\n", __func__);
        exit(1);
    }


    while (modcaps) {
        capng_act_t action;
        int cap;

        char *next = strchr(modcaps, ':');
        if (next) {
            *next = '\0';
            next++;
        }

        switch (modcaps[0]) {
        case '+':
            action = CAPNG_ADD;
            break;

        case '-':
            action = CAPNG_DROP;
            break;

        default:
            fuse_log(FUSE_LOG_ERR,
                     "%s: Expecting '+'/'-' in modcaps but found '%c'\n",
                     __func__, modcaps[0]);
            exit(1);
        }
        cap = capng_name_to_capability(modcaps + 1);
        if (cap < 0) {
            fuse_log(FUSE_LOG_ERR, "%s: Unknown capability '%s'\n", __func__,
                     modcaps);
            exit(1);
        }
        if (capng_update(action, CAPNG_PERMITTED | CAPNG_EFFECTIVE, cap)) {
            fuse_log(FUSE_LOG_ERR, "%s: capng_update failed for '%s'\n",
                     __func__, modcaps);
            exit(1);
        }

        modcaps = next;
    }
    g_free(modcaps_in);

    if (capng_apply(CAPNG_SELECT_BOTH)) {
        fuse_log(FUSE_LOG_ERR, "%s: capng_apply failed\n", __func__);
        exit(1);
    }

    cap.saved = capng_save_state();
    if (!cap.saved) {
        fuse_log(FUSE_LOG_ERR, "%s: capng_save_state failed\n", __func__);
        exit(1);
    }
    pthread_mutex_unlock(&cap.mutex);
}
