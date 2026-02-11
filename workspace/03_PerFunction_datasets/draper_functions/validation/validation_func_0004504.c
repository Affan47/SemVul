readFully(int fd, void *buf, size_t nbyte)
{
    ssize_t remaining = nbyte;
    for (;;) {
        ssize_t n = read(fd, buf, remaining);
        if (n == 0) {
            return nbyte - remaining;
        } else if (n > 0) {
            remaining -= n;
            if (remaining <= 0)
                return nbyte;


            buf = (void *) (((char *)buf) + n);
        } else if (errno == EINTR) {


        } else {
            return -1;
        }
    }
}
