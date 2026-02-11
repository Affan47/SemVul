expSetBlockModeProc(fd, mode)
    int fd;
    int mode;


{
    int curStatus;


#ifndef USE_FIONBIO
    curStatus = fcntl(fd, F_GETFL);

    if (mode == TCL_MODE_BLOCKING) {
	curStatus &= (~(O_NONBLOCK));
    } else {
	curStatus |= O_NONBLOCK;
    }

    if (fcntl(fd, F_SETFL, curStatus) < 0) {
	return errno;
    }
    curStatus = fcntl(fd, F_GETFL);
#else
    if (mode == TCL_MODE_BLOCKING) {
	curStatus = 0;
    } else {
	curStatus = 1;
    }
    if (ioctl(fd, (int) FIONBIO, &curStatus) < 0) {
	return errno;
    }
#endif
    return 0;
}
