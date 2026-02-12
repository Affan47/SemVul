qmp_guest_fstrim(bool has_minimum, int64_t minimum, Error **errp)
{
    GuestFilesystemTrimResponse *response;
    GuestFilesystemTrimResultList *list;
    GuestFilesystemTrimResult *result;
    int ret = 0;
    FsMountList mounts;
    struct FsMount *mount;
    int fd;
    Error *local_err = NULL;
    struct fstrim_range r;

    slog("guest-fstrim called");

    QTAILQ_INIT(&mounts);
    build_fs_mount_list(&mounts, &local_err);
    if (local_err) {
        error_propagate(errp, local_err);
        return NULL;
    }

    response = g_malloc0(sizeof(*response));

    QTAILQ_FOREACH(mount, &mounts, next) {
        result = g_malloc0(sizeof(*result));
        result->path = g_strdup(mount->dirname);

        list = g_malloc0(sizeof(*list));
        list->value = result;
        list->next = response->paths;
        response->paths = list;

        fd = qemu_open(mount->dirname, O_RDONLY);
        if (fd == -1) {
            result->error = g_strdup_printf("failed to open: %s",
                                            strerror(errno));
            result->has_error = true;
            continue;
        }


        r.start = 0;
        r.len = -1;
        r.minlen = has_minimum ? minimum : 0;
        ret = ioctl(fd, FITRIM, &r);
        if (ret == -1) {
            result->has_error = true;
            if (errno == ENOTTY || errno == EOPNOTSUPP) {
                result->error = g_strdup("trim not supported");
            } else {
                result->error = g_strdup_printf("failed to trim: %s",
                                                strerror(errno));
            }
            close(fd);
            continue;
        }

        result->has_minimum = true;
        result->minimum = r.minlen;
        result->has_trimmed = true;
        result->trimmed = r.len;
        close(fd);
    }

    free_fs_mount_list(&mounts);
    return response;
}
