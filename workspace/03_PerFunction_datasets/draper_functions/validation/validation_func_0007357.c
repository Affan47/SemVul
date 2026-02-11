drmGetClient(int fd, int idx, int *auth, int *pid, int *uid,
		 unsigned long *magic, unsigned long *iocs)
{
    drm_client_t client;

    memclear(client);
    client.idx = idx;
    if (drmIoctl(fd, DRM_IOCTL_GET_CLIENT, &client))
	return -errno;
    *auth      = client.auth;
    *pid       = client.pid;
    *uid       = client.uid;
    *magic     = client.magic;
    *iocs      = client.iocs;
    return 0;
}
