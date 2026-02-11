ap_unixd_set_proc_mutex_perms(apr_proc_mutex_t *pmutex)
{
    if (!geteuid()) {
        apr_lockmech_e mech = proc_mutex_mech(pmutex);

        switch(mech) {
#if APR_HAS_SYSVSEM_SERIALIZE
        case APR_LOCK_SYSVSEM:
        {
            apr_os_proc_mutex_t ospmutex;
#if !APR_HAVE_UNION_SEMUN
            union semun {
                long val;
                struct semid_ds *buf;
                unsigned short *array;
            };
#endif
            union semun ick;
            struct semid_ds buf = { { 0 } };

            apr_os_proc_mutex_get(&ospmutex, pmutex);
            buf.sem_perm.uid = ap_unixd_config.user_id;
            buf.sem_perm.gid = ap_unixd_config.group_id;
            buf.sem_perm.mode = 0600;
            ick.buf = &buf;
            if (semctl(ospmutex.crossproc, 0, IPC_SET, ick) < 0) {
                return errno;
            }
        }
        break;
#endif
#if APR_HAS_FLOCK_SERIALIZE
        case APR_LOCK_FLOCK:
        {
            const char *lockfile = apr_proc_mutex_lockfile(pmutex);

            if (lockfile) {
                if (chown(lockfile, ap_unixd_config.user_id,
                          -1 ) < 0) {
                    return errno;
                }
            }
        }
        break;
#endif
        default:

            break;
        }
    }
    return APR_SUCCESS;
}
