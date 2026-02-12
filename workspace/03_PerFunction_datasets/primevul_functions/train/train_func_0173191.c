NsWriterQueue(Ns_Conn *conn, size_t nsend,
              Tcl_Channel chan, FILE *fp, int fd,
              struct iovec *bufs, int nbufs,
              const Ns_FileVec *filebufs, int nfilebufs,
              bool everysize)
{
    Conn          *connPtr;
    WriterSock    *wrSockPtr;
    SpoolerQueue  *queuePtr;
    DrvWriter     *wrPtr;
    bool           trigger = NS_FALSE;
    size_t         headerSize;
    Ns_ReturnCode  status = NS_OK;
    Ns_FileVec    *fbufs = NULL;
    int            nfbufs = 0;

    NS_NONNULL_ASSERT(conn != NULL);
    connPtr = (Conn *)conn;

    if (unlikely(connPtr->sockPtr == NULL)) {
        Ns_Log(Warning,
               "NsWriterQueue: called without sockPtr size %" PRIdz " bufs %d flags %.6x stream %.6x chan %p fd %d",
               nsend, nbufs, connPtr->flags, connPtr->flags & NS_CONN_STREAM,
               (void *)chan, fd);
        status = NS_ERROR;
        wrPtr = NULL;
    } else {

        wrPtr = &connPtr->sockPtr->drvPtr->writer;

        Ns_Log(DriverDebug,
               "NsWriterQueue: size %" PRIdz " bufs %p (%d) flags %.6x stream %.6x chan %p fd %d thread %d",
               nsend, (void *)bufs, nbufs, connPtr->flags, connPtr->flags & NS_CONN_STREAM,
               (void *)chan, fd, wrPtr->threads);

        if (unlikely(wrPtr->threads == 0)) {
            Ns_Log(DriverDebug, "NsWriterQueue: no writer threads configured");
            status = NS_ERROR;

        } else if (nsend < (size_t)wrPtr->writersize && !everysize && connPtr->fd == 0) {
            Ns_Log(DriverDebug, "NsWriterQueue: file is too small(%" PRIdz " < %" PRIdz ")",
                   nsend, wrPtr->writersize);
            status = NS_ERROR;
        }
    }
    if (status != NS_OK) {
        return status;
    }

    assert(wrPtr != NULL);


    if (((connPtr->flags & NS_CONN_STREAM) != 0u) || connPtr->fd > 0) {

        if (wrPtr->doStream == NS_WRITER_STREAM_NONE) {
            status = NS_ERROR;
        } else if (unlikely(fp != NULL || fd != NS_INVALID_FD)) {
            Ns_Log(DriverDebug, "NsWriterQueue: does not stream from this source via writer");
            status = NS_ERROR;
        } else {
            status = WriterSetupStreamingMode(connPtr, bufs, nbufs, &fd);
        }

        if (unlikely(status != NS_OK)) {
            if (status == NS_FILTER_BREAK) {
                status = NS_OK;
            }
            return status;
        }


        assert(fd != NS_INVALID_FD);

    } else {
        if (fp != NULL) {


            fd = ns_dup(fileno(fp));
        } else if (fd != NS_INVALID_FD) {


            fd = ns_dup(fd);
        } else if (chan != NULL) {
            ClientData clientData;


            if (Tcl_GetChannelHandle(chan, TCL_READABLE, &clientData) != TCL_OK) {
                return NS_ERROR;
            }
            fd = ns_dup(PTR2INT(clientData));
        } else if (filebufs != NULL && nfilebufs > 0) {


            size_t i;


            fbufs = (Ns_FileVec *)ns_calloc((size_t)nfilebufs, sizeof(Ns_FileVec));
            nfbufs = nfilebufs;

            for (i = 0u; i < (size_t)nfilebufs; i++) {
                fbufs[i].fd = ns_dup(filebufs[i].fd);
                fbufs[i].length = filebufs[i].length;
                fbufs[i].offset = filebufs[i].offset;
            }


            fd = fbufs[0].fd;

            Ns_Log(DriverDebug, "NsWriterQueue: filevec mode, take first fd %d tosend %lu", fd, nsend);
        }
    }

    Ns_Log(DriverDebug, "NsWriterQueue: writer threads %d nsend %" PRIdz " writersize %" PRIdz,
           wrPtr->threads, nsend, wrPtr->writersize);

    assert(connPtr->poolPtr != NULL);
    connPtr->poolPtr->stats.spool++;

    wrSockPtr = (WriterSock *)ns_calloc(1u, sizeof(WriterSock));
    wrSockPtr->sockPtr = connPtr->sockPtr;
    wrSockPtr->poolPtr = connPtr->poolPtr;
    wrSockPtr->sockPtr->timeout.sec = 0;
    wrSockPtr->flags = connPtr->flags;
    wrSockPtr->refCount = 1;


    wrSockPtr->rateLimit = connPtr->rateLimit;
    if (wrSockPtr->rateLimit == -1) {


        if (connPtr->poolPtr->rate.poolLimit > 0) {


            wrSockPtr->rateLimit = connPtr->poolPtr->rate.poolLimit / 2;
        } else {
            wrSockPtr->rateLimit = wrPtr->rateLimit;
        }
    }
    Ns_Log(WriterDebug, "### Writer(%d): initial rate limit %d KB/s",
           wrSockPtr->sockPtr->sock, wrSockPtr->rateLimit);


    Ns_ConnSetLengthHeader(conn, nsend, (wrSockPtr->flags & NS_CONN_STREAM) != 0u);


    if ((conn->flags & NS_CONN_SENTHDRS) == 0u) {
        Tcl_DString    ds;

        Ns_DStringInit(&ds);
        Ns_Log(DriverDebug, "### Writer(%d): add header", fd);
        conn->flags |= NS_CONN_SENTHDRS;
        (void)Ns_CompleteHeaders(conn, nsend, 0u, &ds);

        headerSize = (size_t)Ns_DStringLength(&ds);
        if (headerSize > 0u) {
            wrSockPtr->headerString = ns_strdup(Tcl_DStringValue(&ds));
        }
        Ns_DStringFree(&ds);
    } else {
        headerSize = 0u;
    }

    if (fd != NS_INVALID_FD) {


        wrSockPtr->fd = fd;
        wrSockPtr->c.file.bufs = fbufs;
        wrSockPtr->c.file.nbufs = nfbufs;

        Ns_Log(DriverDebug, "### Writer(%d) tosend %" PRIdz " files %d bufsize %" PRIdz,
               fd, nsend, nfbufs, wrPtr->bufsize);

        if (unlikely(headerSize >= wrPtr->bufsize)) {


            wrSockPtr->c.file.buf = (unsigned char *)wrSockPtr->headerString;
            wrSockPtr->c.file.maxsize = headerSize;
            wrSockPtr->c.file.bufsize = headerSize;
            wrSockPtr->headerString = NULL;
        } else if (headerSize > 0u) {


            wrSockPtr->c.file.buf = ns_malloc(wrPtr->bufsize);
            memcpy(wrSockPtr->c.file.buf, wrSockPtr->headerString, headerSize);
            wrSockPtr->c.file.bufsize = headerSize;
            wrSockPtr->c.file.maxsize = wrPtr->bufsize;
            ns_free(wrSockPtr->headerString);
            wrSockPtr->headerString = NULL;
        } else {
            assert(wrSockPtr->headerString == NULL);
            wrSockPtr->c.file.buf = ns_malloc(wrPtr->bufsize);
            wrSockPtr->c.file.maxsize = wrPtr->bufsize;
        }
        wrSockPtr->c.file.bufoffset = 0;
        wrSockPtr->c.file.toRead = nsend;

    } else if (bufs != NULL) {
        int   i, j, headerbufs = (headerSize > 0u ? 1 : 0);

        wrSockPtr->fd = NS_INVALID_FD;

        if (nbufs+headerbufs < UIO_SMALLIOV) {
            wrSockPtr->c.mem.bufs = wrSockPtr->c.mem.preallocated_bufs;
        } else {
            Ns_Log(DriverDebug, "NsWriterQueue: alloc %d iovecs", nbufs);
            wrSockPtr->c.mem.bufs = ns_calloc((size_t)nbufs + (size_t)headerbufs, sizeof(struct iovec));
        }
        wrSockPtr->c.mem.nbufs = nbufs+headerbufs;
        if (headerbufs != 0) {
            wrSockPtr->c.mem.bufs[0].iov_base = wrSockPtr->headerString;
            wrSockPtr->c.mem.bufs[0].iov_len  = headerSize;
        }

        if (connPtr->fmap.addr != NULL) {
            Ns_Log(DriverDebug, "NsWriterQueue: deliver fmapped %p", (void *)connPtr->fmap.addr);


            for (i = 0, j=headerbufs; i < nbufs; i++, j++) {
                wrSockPtr->c.mem.bufs[j].iov_base = bufs[i].iov_base;
                wrSockPtr->c.mem.bufs[j].iov_len  = bufs[i].iov_len;
            }


            wrSockPtr->c.mem.fmap = connPtr->fmap;
            connPtr->fmap.addr = NULL;


        } else {


            for (i = 0, j=headerbufs; i < nbufs; i++, j++) {
                wrSockPtr->c.mem.bufs[j].iov_base = ns_malloc(bufs[i].iov_len);
                wrSockPtr->c.mem.bufs[j].iov_len  = bufs[i].iov_len;
                memcpy(wrSockPtr->c.mem.bufs[j].iov_base, bufs[i].iov_base, bufs[i].iov_len);
            }

            wrSockPtr->headerString = NULL;
        }

    } else {
        ns_free(wrSockPtr);
        return NS_ERROR;
    }


    nsend += headerSize;


    if (connPtr->clientData != NULL) {
        wrSockPtr->clientData = ns_strdup(connPtr->clientData);
    }
    wrSockPtr->startTime = *Ns_ConnStartTime(conn);


    if ((wrSockPtr->flags & NS_CONN_STREAM) != 0u) {
        wrSockPtr->doStream = NS_WRITER_STREAM_ACTIVE;
        assert(connPtr->strWriter == NULL);


        connPtr->strWriter = (NsWriterSock *)wrSockPtr;
        wrSockPtr->connPtr = connPtr;
    }


    connPtr->flags |= NS_CONN_SENT_VIA_WRITER;
    wrSockPtr->keep = connPtr->keep > 0 ? NS_TRUE : NS_FALSE;
    wrSockPtr->size = nsend;
    Ns_Log(DriverDebug, "NsWriterQueue NS_CONN_SENT_VIA_WRITER connPtr %p",
           (void*)connPtr);

    if ((wrSockPtr->flags & NS_CONN_STREAM) == 0u) {
        Ns_Log(DriverDebug, "NsWriterQueue NS_CONN_SENT_VIA_WRITER connPtr %p clear sockPtr %p",
               (void*)connPtr, (void*)connPtr->sockPtr);
        connPtr->sockPtr = NULL;
        connPtr->flags |= NS_CONN_CLOSED;
        connPtr->nContentSent = nsend - headerSize;
    }


    Ns_MutexLock(&wrPtr->lock);
    if (wrPtr->curPtr == NULL) {
        wrPtr->curPtr = wrPtr->firstPtr;
    }
    queuePtr = wrPtr->curPtr;
    wrPtr->curPtr = wrPtr->curPtr->nextPtr;
    Ns_MutexUnlock(&wrPtr->lock);

    Ns_Log(WriterDebug, "Writer(%d): started: id=%d fd=%d, "
           "size=%" PRIdz ", flags=%X, rate %d KB/s: %s",
           wrSockPtr->sockPtr->sock,
           queuePtr->id, wrSockPtr->fd,
           nsend, wrSockPtr->flags,
           wrSockPtr->rateLimit,
           connPtr->request.line);


    wrSockPtr->queuePtr = queuePtr;

    Ns_MutexLock(&queuePtr->lock);
    if (queuePtr->sockPtr == NULL) {
        trigger = NS_TRUE;
    }

    Push(wrSockPtr, queuePtr->sockPtr);
    Ns_MutexUnlock(&queuePtr->lock);


    if (trigger) {
        SockTrigger(queuePtr->pipe[1]);
    }

    return NS_OK;
}
