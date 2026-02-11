open(int flags)
{
    bool requestWrite = ((flags & O_RDWR) || (flags & O_WRONLY));

    rDebug("open call for %s file", requestWrite ? "writable" : "read only");

    int result = 0;


    if((fd >= 0) && (canWrite || !requestWrite))
    {
	rDebug("using existing file descriptor");
	result = fd;
    } else
    {
	int finalFlags = requestWrite ? O_RDWR : O_RDONLY;

#if defined(O_LARGEFILE)
	if( flags & O_LARGEFILE )
	    finalFlags |= O_LARGEFILE;
#else
#warning O_LARGEFILE not supported
#endif

	int newFd = ::open( name.c_str(), finalFlags );

	rDebug("open file with flags %i, result = %i", finalFlags, newFd);

	if((newFd == -1) && (errno == EACCES))
	{
	    rDebug("using readonly workaround for open");
	    newFd = open_readonly_workaround( name.c_str(), finalFlags );
	}

	if(newFd >= 0)
	{
	    if(oldfd >= 0)
	    {
		rError("leaking FD?: oldfd = %i, fd = %i, newfd = %i",
			oldfd, fd, newFd);
	    }


	    canWrite = requestWrite;
	    oldfd = fd;
	    result = fd = newFd;
	} else
	{
	    result = -errno;
	    rInfo("::open error: %s", strerror(errno));
	}
    }

    if(result < 0)
	rInfo("file %s open failure: %i", name.c_str(), -result);

    return result;
}
