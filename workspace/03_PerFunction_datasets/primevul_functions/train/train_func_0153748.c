static void transfer_memory_block(GuestMemoryBlock *mem_blk, bool sys2memblk,
                                  GuestMemoryBlockResponse *result,
                                  Error **errp)
{
    char *dirpath;
    int dirfd;
    char *status;
    Error *local_err = NULL;

    if (!sys2memblk) {
        DIR *dp;

        if (!result) {
            error_setg(errp, "Internal error, 'result' should not be NULL");
            return;
        }
        errno = 0;
        dp = opendir("/sys/devices/system/memory/");


        if (!dp) {
            if (errno == ENOENT) {
                result->response =
                    GUEST_MEMORY_BLOCK_RESPONSE_TYPE_OPERATION_NOT_SUPPORTED;
            }
            goto out1;
        }
        closedir(dp);
    }

    dirpath = g_strdup_printf("/sys/devices/system/memory/memory%" PRId64 "/",
                              mem_blk->phys_index);
    dirfd = open(dirpath, O_RDONLY | O_DIRECTORY);
    if (dirfd == -1) {
        if (sys2memblk) {
            error_setg_errno(errp, errno, "open(\"%s\")", dirpath);
        } else {
            if (errno == ENOENT) {
                result->response = GUEST_MEMORY_BLOCK_RESPONSE_TYPE_NOT_FOUND;
            } else {
                result->response =
                    GUEST_MEMORY_BLOCK_RESPONSE_TYPE_OPERATION_FAILED;
            }
        }
        g_free(dirpath);
        goto out1;
    }
    g_free(dirpath);

    status = g_malloc0(10);
    ga_read_sysfs_file(dirfd, "state", status, 10, &local_err);
    if (local_err) {

        if (errno == ENOENT) {
            error_free(local_err);
            if (sys2memblk) {
                mem_blk->online = true;
                mem_blk->can_offline = false;
            } else if (!mem_blk->online) {
                result->response =
                    GUEST_MEMORY_BLOCK_RESPONSE_TYPE_OPERATION_NOT_SUPPORTED;
            }
        } else {
            if (sys2memblk) {
                error_propagate(errp, local_err);
            } else {
                result->response =
                    GUEST_MEMORY_BLOCK_RESPONSE_TYPE_OPERATION_FAILED;
            }
        }
        goto out2;
    }

    if (sys2memblk) {
        char removable = '0';

        mem_blk->online = (strncmp(status, "online", 6) == 0);

        ga_read_sysfs_file(dirfd, "removable", &removable, 1, &local_err);
        if (local_err) {

            if (errno == ENOENT) {
                error_free(local_err);
                mem_blk->can_offline = false;
            } else {
                error_propagate(errp, local_err);
            }
        } else {
            mem_blk->can_offline = (removable != '0');
        }
    } else {
        if (mem_blk->online != (strncmp(status, "online", 6) == 0)) {
            const char *new_state = mem_blk->online ? "online" : "offline";

            ga_write_sysfs_file(dirfd, "state", new_state, strlen(new_state),
                                &local_err);
            if (local_err) {
                error_free(local_err);
                result->response =
                    GUEST_MEMORY_BLOCK_RESPONSE_TYPE_OPERATION_FAILED;
                goto out2;
            }

            result->response = GUEST_MEMORY_BLOCK_RESPONSE_TYPE_SUCCESS;
            result->has_error_code = false;
        }
    }
    g_free(status);
    close(dirfd);
    return;

out2:
    g_free(status);
    close(dirfd);
out1:
    if (!sys2memblk) {
        result->has_error_code = true;
        result->error_code = errno;
    }
}
