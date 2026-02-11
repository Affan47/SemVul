check_prepare_mountbroker_root (char *mountbroker_root)
{
        int dfd0        = -1;
        int dfd         = -1;
        int dfd2        = -1;
        struct stat st  = {0,};
        struct stat st2 = {0,};
        int ret         = 0;

        ret = open (mountbroker_root, O_RDONLY);
        if (ret != -1) {
                dfd = ret;
                ret = fstat (dfd, &st);
        }
        if (ret == -1 || !S_ISDIR (st.st_mode)) {
                gf_log ("", GF_LOG_ERROR,
                        "cannot access mountbroker-root directory %s",
                        mountbroker_root);
                ret = -1;
                goto out;
        }
        if (st.st_uid != 0 ||
            (st.st_mode & (S_IWGRP|S_IWOTH))) {
                gf_log ("", GF_LOG_ERROR,
                        "permissions on mountbroker-root directory %s are "
                        "too liberal", mountbroker_root);
                ret = -1;
                goto out;
        }

        dfd0 = dup (dfd);

        for (;;) {
                ret = openat (dfd, "..", O_RDONLY);
                if (ret != -1) {
                        dfd2 = ret;
                        ret = fstat (dfd2, &st2);
                }
                if (ret == -1) {
                        gf_log ("", GF_LOG_ERROR,
                                "error while checking mountbroker-root ancestors "
                                "%d (%s)", errno, strerror (errno));
                        goto out;
                }

                if (st2.st_ino == st.st_ino)
                        break;

                if (st2.st_uid != 0 ||
                    ((st2.st_mode & (S_IWGRP|S_IWOTH)) &&
                     !(st2.st_mode & S_ISVTX))) {
                        gf_log ("", GF_LOG_ERROR,
                                "permissions on ancestors of mountbroker-root "
                                "directory are too liberal");
                        ret = -1;
                        goto out;
                }

                close (dfd);
                dfd = dfd2;
                st = st2;
        }

        ret = mkdirat (dfd0, MB_HIVE, 0711);
        if (ret == -1 && errno == EEXIST)
                ret = 0;
        if (ret != -1)
                ret = fstatat (dfd0, MB_HIVE, &st, AT_SYMLINK_NOFOLLOW);
        if (ret == -1 || st.st_mode != (S_IFDIR|0711)) {
                gf_log ("", GF_LOG_ERROR,
                        "failed to set up mountbroker-root directory %s",
                        mountbroker_root);
                ret = -1;
                goto out;
        }

        ret = 0;

 out:
        close (dfd0);
        close (dfd);
        close (dfd2);

        return ret;
}
