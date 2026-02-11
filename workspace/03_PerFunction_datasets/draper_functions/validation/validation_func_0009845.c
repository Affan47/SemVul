drmCommandNone(int fd, unsigned long drmCommandIndex)
{
    void *data = NULL;
    unsigned long request;

    request = DRM_IO( DRM_COMMAND_BASE + drmCommandIndex);

    if (drmIoctl(fd, request, data)) {
	return -errno;
    }
    return 0;
}
