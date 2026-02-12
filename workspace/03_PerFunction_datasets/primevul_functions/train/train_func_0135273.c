static int oss_get_version (int fd, int *version, const char *typ)
{
    if (ioctl (fd, OSS_GETVERSION, &version)) {
#if defined(__FreeBSD__) || defined(__FreeBSD_kernel__)


        if (errno == EINVAL) {
            *version = 0x040000;
            return 0;
        }
#endif
        oss_logerr2 (errno, typ, "Failed to get OSS version\n");
        return -1;
    }
    return 0;
}
