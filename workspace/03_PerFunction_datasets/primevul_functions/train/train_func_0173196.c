WriterSetupStreamingMode(Conn *connPtr, struct iovec *bufs, int nbufs, int *fdPtr)
{
    bool           first;
    size_t         wrote = 0u;
    WriterSock    *wrSockPtr1;
    Ns_ReturnCode  status = NS_OK;

    NS_NONNULL_ASSERT(connPtr != NULL);
    NS_NONNULL_ASSERT(bufs != NULL);
    NS_NONNULL_ASSERT(fdPtr != NULL);

    Ns_Log(DriverDebug, "NsWriterQueue: streaming writer job");

    if (connPtr->fd == 0) {


        first = NS_TRUE;
        wrSockPtr1 = NULL;

        *fdPtr = Ns_GetTemp();
        connPtr->fd = *fdPtr;

        Ns_Log(DriverDebug, "NsWriterQueue: new tmp file has fd %d", *fdPtr);

    } else {


        first = NS_FALSE;
        wrSockPtr1 = WriterSockRequire(connPtr);

        if (wrSockPtr1 == NULL) {
            Ns_Log(Notice,
                   "NsWriterQueue: writer job was already canceled (fd %d); maybe user dropped connection",
                   connPtr->fd);
            return NS_ERROR;

        } else {


            Ns_MutexLock(&wrSockPtr1->c.file.fdlock);
            (void)ns_lseek(connPtr->fd, 0, SEEK_END);
        }
    }


    {
        int i;

        for (i = 0; i < nbufs; i++) {
            ssize_t j = ns_write(connPtr->fd, bufs[i].iov_base, bufs[i].iov_len);

            if (j > 0) {
                wrote += (size_t)j;
                Ns_Log(Debug, "NsWriterQueue: fd %d [%d] spooled %" PRIdz " of %" PRIiovlen " OK %d",
                       connPtr->fd, i, j, bufs[i].iov_len, (j == (ssize_t)bufs[i].iov_len));
            } else {
                Ns_Log(Warning, "NsWriterQueue: spool to fd %d write operation failed",
                       connPtr->fd);
            }
        }
    }

    if (first) {

        connPtr->nContentSent = wrote;
#ifndef _WIN32


        (void)ns_sock_set_blocking(connPtr->fd, NS_FALSE);
#endif


    } else {
        WriterSock *writerSockPtr;


        assert(wrSockPtr1 != NULL);


        writerSockPtr = (WriterSock *)connPtr->strWriter;
        writerSockPtr->size += wrote;
        writerSockPtr->c.file.toRead += wrote;
        Ns_MutexUnlock(&wrSockPtr1->c.file.fdlock);

        connPtr->nContentSent += wrote;
        if (likely(wrSockPtr1->queuePtr != NULL)) {
            SockTrigger(wrSockPtr1->queuePtr->pipe[1]);
        }
        WriterSockRelease(wrSockPtr1);
        status = NS_FILTER_BREAK;
    }

    return status;
}
