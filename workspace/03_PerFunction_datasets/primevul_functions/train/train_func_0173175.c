NsAsyncWrite(int fd, const char *buffer, size_t nbyte)
{
    Ns_ReturnCode returnCode = NS_OK;

    NS_NONNULL_ASSERT(buffer != NULL);


    if (asyncWriter == NULL || asyncWriter->firstPtr->stopped) {
        ssize_t written = ns_write(fd, buffer, nbyte);

        if (unlikely(written != (ssize_t)nbyte)) {
            int retries = 100;


            returnCode = NS_ERROR;
            do {
                if (written < 0) {
                    fprintf(stderr, "error during async write (fd %d): %s\n",
                           fd, strerror(errno));
                    break;
                }


                WriteWarningRaw("partial write", fd, nbyte, written);
                nbyte -= (size_t)written;
                buffer += written;
                written = ns_write(fd, buffer, nbyte);
                if (written == (ssize_t)nbyte) {
                    returnCode = NS_OK;
                    break;
                }
            } while (retries-- > 0);
        }

    } else {
        SpoolerQueue         *queuePtr;
        bool                  trigger = NS_FALSE;
        const AsyncWriteData *wdPtr;
        AsyncWriteData       *newWdPtr;


        newWdPtr = ns_calloc(1u, sizeof(AsyncWriteData));
        newWdPtr->fd = fd;
        newWdPtr->bufsize = nbyte;
        newWdPtr->data = ns_malloc(nbyte + 1u);
        memcpy(newWdPtr->data, buffer, newWdPtr->bufsize);
        newWdPtr->buf  = newWdPtr->data;
        newWdPtr->size = newWdPtr->bufsize;


        queuePtr = asyncWriter->firstPtr;
        assert(queuePtr != NULL);

        Ns_MutexLock(&queuePtr->lock);
        wdPtr = queuePtr->sockPtr;
        if (wdPtr != NULL) {
            newWdPtr->nextPtr = queuePtr->sockPtr;
            queuePtr->sockPtr = newWdPtr;
        } else {
            queuePtr->sockPtr = newWdPtr;
            trigger = NS_TRUE;
        }
        Ns_MutexUnlock(&queuePtr->lock);


        if (trigger) {
            SockTrigger(queuePtr->pipe[1]);
        }
    }

    return returnCode;
}
