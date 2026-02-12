WriterReadFromSpool(WriterSock *curPtr) {
    NsWriterStreamState doStream;
    SpoolerState        status = SPOOLER_OK;
    size_t              maxsize, toRead;
    unsigned char      *bufPtr;

    NS_NONNULL_ASSERT(curPtr != NULL);

    doStream = curPtr->doStream;
    if (doStream != NS_WRITER_STREAM_NONE) {
        Ns_MutexLock(&curPtr->c.file.fdlock);
        toRead = curPtr->c.file.toRead;
        Ns_MutexUnlock(&curPtr->c.file.fdlock);
    } else {
        toRead = curPtr->c.file.toRead;

        Ns_Log(DriverDebug, "### WriterReadFromSpool [%d]: fd %d tosend %lu files %d",
                curPtr->c.file.currentbuf, curPtr->fd, toRead, curPtr->c.file.nbufs);
    }

    maxsize = curPtr->c.file.maxsize;
    bufPtr  = curPtr->c.file.buf;


    if (curPtr->c.file.bufsize > 0u) {
        Ns_Log(DriverDebug,
               "### WriterReadFromSpool %p %.6x leftover %" PRIdz " offset %ld",
               (void *)curPtr,
               curPtr->flags,
               curPtr->c.file.bufsize,
               (long)curPtr->c.file.bufoffset);
        if (likely(curPtr->c.file.bufoffset > 0)) {
            memmove(curPtr->c.file.buf,
                    curPtr->c.file.buf + curPtr->c.file.bufoffset,
                    curPtr->c.file.bufsize);
        }
        bufPtr = curPtr->c.file.buf + curPtr->c.file.bufsize;
        maxsize -= curPtr->c.file.bufsize;
    }
    if (toRead > maxsize) {
        toRead = maxsize;
    }


    if (toRead > 0u) {
        ssize_t n;

        if (doStream != NS_WRITER_STREAM_NONE) {


            Ns_MutexLock(&curPtr->c.file.fdlock);
            (void) ns_lseek(curPtr->fd, (off_t)curPtr->nsent, SEEK_SET);
        }

        if (curPtr->c.file.nbufs == 0) {


            n = ns_read(curPtr->fd, bufPtr, toRead);

        } else {


            int    currentbuf = curPtr->c.file.currentbuf;
            size_t wantRead = curPtr->c.file.bufs[currentbuf].length;
            size_t segSize = (wantRead > toRead ? toRead : wantRead);

            n = ns_read(curPtr->fd, bufPtr, segSize);

            Ns_Log(DriverDebug, "### WriterReadFromSpool [%d] (nbufs %d): read from fd %d want %lu got %ld (remain %lu)",
                   currentbuf, curPtr->c.file.nbufs, curPtr->fd,  segSize, n, wantRead);

            if (n > 0) {


                curPtr->c.file.bufs[currentbuf].length -= (size_t)n;

                if ((size_t)n < wantRead) {


                    Ns_Log(DriverDebug, "### WriterReadFromSpool [%d] (nbufs %d): partial read on fd %d (got %ld)",
                           currentbuf, curPtr->c.file.nbufs,
                           curPtr->fd, n);

                } else if (currentbuf < curPtr->c.file.nbufs - 1 ) {


                    ns_close(curPtr->fd);
                    curPtr->c.file.bufs[currentbuf].fd = NS_INVALID_FD;

                    curPtr->c.file.currentbuf ++;
                    curPtr->fd = curPtr->c.file.bufs[curPtr->c.file.currentbuf].fd;

                    Ns_Log(DriverDebug, "### WriterReadFromSpool switch to [%d] fd %d",
                           curPtr->c.file.currentbuf, curPtr->fd);
                }
            }
        }

        if (n <= 0) {
            status = SPOOLER_READERROR;
        } else {


            curPtr->c.file.toRead -= (size_t)n;
            curPtr->c.file.bufsize += (size_t)n;
        }

        if (doStream != NS_WRITER_STREAM_NONE) {
            Ns_MutexUnlock(&curPtr->c.file.fdlock);
        }
    }

    return status;
}
