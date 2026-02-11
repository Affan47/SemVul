drmScatterGatherAlloc(int fd, unsigned long size, drm_handle_t *handle)
{
    drm_scatter_gather_t sg;

    memclear(sg);

    *handle = 0;
    sg.size   = size;
    if (drmIoctl(fd, DRM_IOCTL_SG_ALLOC, &sg))
	return -errno;
    *handle = sg.handle;
    return 0;
}
