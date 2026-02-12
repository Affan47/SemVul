void dodele(char *name)
{
#ifndef ANON_CAN_DELETE
    if (guest != 0) {
        addreply_noformat(550, MSG_ANON_CANT_DELETE);
        return;
    }
#endif
    if (name == NULL || *name == 0) {
        addreply_noformat(501, MSG_NO_FILE_NAME);
        return;
    }
    if (checknamesanity(name, dot_write_ok) != 0) {
        addreply(553, MSG_SANITY_FILE_FAILURE, name);
        return;
    }
    if (keepallfiles != 0) {
#ifdef EPERM
        errno = EPERM;
#else
        errno = 1;
#endif
        goto denied;
    }


#ifdef QUOTAS
    {
        char *p;
        struct stat st;
        struct stat st2;
        size_t dirlen = (size_t) 0U;
        char qtfile[PATH_MAX + 1];

        if ((p = strrchr(name, '/')) != NULL) {
            if ((dirlen = p - name + (size_t) 1U) >= sizeof qtfile) {
                goto denied;
            }
            memcpy(qtfile, name, dirlen);
        }
        if (SNCHECK(snprintf(qtfile + dirlen, sizeof qtfile - dirlen,
                             PUREFTPD_TMPFILE_PREFIX "rename.%lu.%x",
                             (unsigned long) getpid(), zrand()),
                    sizeof qtfile)) {
            goto denied;
        }
        if (lstat(name, &st) != 0) {
            goto denied;
        }
        if (!S_ISREG(st.st_mode)
# ifndef NEVER_DELETE_SYMLINKS
            && !S_ISLNK(st.st_mode)
# endif
            ) {
# ifdef EINVAL
            errno = EINVAL;
# endif
            goto denied;
        }
        if (rename(name, qtfile) != 0) {
            goto denied;
        }
        if (lstat(qtfile, &st2) != 0 ||
            st.st_dev != st2.st_dev ||
            st.st_ino != st2.st_ino ||
            st.st_size != st2.st_size) {
# ifdef EINVAL
            errno = EINVAL;
# endif
            goto denied;
        }
        if (unlink(qtfile) < 0) {


            (void) rename(qtfile, name);
            goto denied;
        }
        {
            Quota quota;

            if (quota_update(&quota, -1LL,
                             -((long long) st.st_size), NULL) == 0) {
                displayquota(&quota);
            }
        }
    }
#else
    if (unlink(name) < 0) {
        goto denied;
    }
#endif
    addreply(250, MSG_DELE_SUCCESS, "", "", "", name);
    logfile(LOG_NOTICE, MSG_DELE_SUCCESS, root_directory,
            *name == '/' ? "" : wd,
            (*name != '/' && (!*wd || wd[strlen(wd) - 1] != '/'))
            ? "/" : "", name);
    return;

    denied:
    addreply(550, MSG_DELE_FAILED ": %s", name, strerror(errno));
}
