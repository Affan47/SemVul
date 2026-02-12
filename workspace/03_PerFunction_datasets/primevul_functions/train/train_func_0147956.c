lyp_mmap(struct ly_ctx *ctx, int fd, size_t addsize, size_t *length, void **addr)
{
    struct stat sb;
    long pagesize;
    size_t m;

    assert(fd >= 0);
    if (fstat(fd, &sb) == -1) {
        LOGERR(ctx, LY_ESYS, "Failed to stat the file descriptor (%s) for the mmap().", strerror(errno));
        return 1;
    }
    if (!S_ISREG(sb.st_mode)) {
        LOGERR(ctx, LY_EINVAL, "File to mmap() is not a regular file.");
        return 1;
    }
    if (!sb.st_size) {
        *addr = NULL;
        return 0;
    }
    pagesize = sysconf(_SC_PAGESIZE);
    ++addsize;

    m = sb.st_size % pagesize;
    if (m && pagesize - m >= addsize) {

        *length = sb.st_size + addsize;
        *addr = mmap(NULL, *length, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    } else {


        *length = sb.st_size + pagesize;
        *addr = mmap(NULL, *length, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        *addr = mmap(*addr, sb.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_FIXED, fd, 0);
    }
    if (*addr == MAP_FAILED) {
        LOGERR(ctx, LY_ESYS, "mmap() failed (%s).", strerror(errno));
        return 1;
    }

    return 0;
}
