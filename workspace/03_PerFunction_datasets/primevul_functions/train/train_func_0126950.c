static int drop_security_capability(const struct lo_data *lo, int fd)
{
    if (!lo->xattr_security_capability) {

        return 0;
    }
    if (!fremovexattr(fd, lo->xattr_security_capability)) {

        return 0;
    }

    switch (errno) {
    case ENODATA:

        return 0;

    case ENOTSUP:

        return 0;

    default:

        return errno;
    }
}
