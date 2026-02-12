psutil_pid_exists(long pid) {
    int ret;


    if (pid < 0)
        return 0;


    if (pid == 0) {
#if defined(PSUTIL_LINUX) || defined(PSUTIL_FREEBSD)
        return 0;
#else
        return 1;
#endif
    }

#if defined(PSUTIL_OSX)
    ret = kill((pid_t)pid , 0);
#else
    ret = kill(pid , 0);
#endif

    if (ret == 0)
        return 1;
    else {
        if (errno == ESRCH) {

            return 0;
        }
        else if (errno == EPERM) {


            return 1;
        }
        else {


            PyErr_SetFromErrno(PyExc_OSError);
            return -1;
        }
    }
}
