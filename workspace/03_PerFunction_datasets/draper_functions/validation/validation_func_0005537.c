GC_write(int fd, const char *buf, size_t len)
{
     int bytes_written = 0;
     int result;
     IF_CANCEL(int cancel_state;)

     DISABLE_CANCEL(cancel_state);
     while (bytes_written < len) {
#       ifdef GC_SOLARIS_THREADS
            result = syscall(SYS_write, fd, buf + bytes_written,
                                            len - bytes_written);
#       else
            result = write(fd, buf + bytes_written, len - bytes_written);
#       endif
        if (-1 == result) {
            RESTORE_CANCEL(cancel_state);
            return(result);
        }
        bytes_written += result;
    }
    RESTORE_CANCEL(cancel_state);
    return(bytes_written);
}
