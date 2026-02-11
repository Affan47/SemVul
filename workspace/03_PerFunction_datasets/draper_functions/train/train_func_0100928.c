xioctl(int fd, int cmd, void *arg, int mayfail)
{
    int rc;

#ifndef USE_LIBV4L
    rc = ioctl(fd,cmd,arg);
#else
    rc = v4l2_ioctl(fd,cmd,arg);
#endif
    if (rc >= 0 && ng_debug < 2)
	return rc;
    if (mayfail && ((errno == EINVAL) || (errno == ENOTTY)) && ng_debug < 2)
	return rc;
#ifdef HAVE_EXPLAIN
    fprintf(stderr,"v4l2: %s\n",(rc >= 0) ? "ok" : explain_ioctl(fd,cmd,arg));
#else
    print_ioctl(stderr,ioctls_v4l2,PREFIX,cmd,arg);
    fprintf(stderr,": %s\n",(rc >= 0) ? "ok" : strerror(errno));
#endif
    return rc;
}
