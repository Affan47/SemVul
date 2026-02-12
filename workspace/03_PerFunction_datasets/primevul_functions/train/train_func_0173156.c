SockRead(Sock *sockPtr, int spooler, const Ns_Time *timePtr)
{
    const Driver       *drvPtr;
    Request      *reqPtr;
    Tcl_DString  *bufPtr;
    struct iovec  buf;
    char          tbuf[16384];
    size_t        buflen, nread;
    ssize_t       n;
    SockState     resultState;

    NS_NONNULL_ASSERT(sockPtr != NULL);
    drvPtr = sockPtr->drvPtr;

    tbuf[0] = '\0';


    if (sockPtr->acceptTime.sec == 0) {
        assert(timePtr != NULL);
        sockPtr->acceptTime = *timePtr;
    }


    if (sockPtr->reqPtr == NULL) {
        RequestNew(sockPtr);
    }


    reqPtr = sockPtr->reqPtr;
    bufPtr = &reqPtr->buffer;
    if (reqPtr->length == 0u) {
        nread = drvPtr->bufsize;
    } else {
        nread = reqPtr->length - reqPtr->avail;
    }


    buflen = (size_t)bufPtr->length;
    n = (ssize_t)(buflen + nread);
    if (unlikely(n > drvPtr->maxinput)) {
        n = (ssize_t)drvPtr->maxinput;
        nread = (size_t)n - buflen;
        if (nread == 0u) {
            Ns_Log(DriverDebug, "SockRead: maxinput reached %" TCL_LL_MODIFIER "d",
                   drvPtr->maxinput);
            return SOCK_ERROR;
        }
    }


#ifndef _WIN32
    if (reqPtr->coff > 0u
        && !reqPtr->chunkStartOff
        && reqPtr->length > (size_t)drvPtr->readahead
        && sockPtr->tfd <= 0
        ) {
        const DrvSpooler *spPtr = &drvPtr->spooler;

        Ns_Log(DriverDebug, "SockRead: require tmp file for content spooling (length %" PRIuz" > readahead "
               "%" TCL_LL_MODIFIER "d)",
               reqPtr->length, drvPtr->readahead);


        if (spooler == 0 && spPtr->threads > 0) {
            return SOCK_SPOOL;
        }


        if (drvPtr->maxupload > 0
            && reqPtr->length > (size_t)drvPtr->maxupload
            ) {
            size_t tfileLength = strlen(drvPtr->uploadpath) + 16u;

            sockPtr->tfile = ns_malloc(tfileLength);
            snprintf(sockPtr->tfile, tfileLength, "%s/%d.XXXXXX", drvPtr->uploadpath, sockPtr->sock);
            sockPtr->tfd = ns_mkstemp(sockPtr->tfile);
            if (sockPtr->tfd == NS_INVALID_FD) {
                Ns_Log(Error, "SockRead: cannot create spool file with template '%s': %s",
                       sockPtr->tfile, strerror(errno));
            }
        } else {


            sockPtr->tfd = Ns_GetTemp();
        }

        if (unlikely(sockPtr->tfd == NS_INVALID_FD)) {
            Ns_Log(DriverDebug, "SockRead: spool fd invalid");
            return SOCK_ERROR;
        }

        n = (ssize_t)((size_t)bufPtr->length - reqPtr->coff);
        assert(n >= 0);
        if (ns_write(sockPtr->tfd, bufPtr->string + reqPtr->coff, (size_t)n) != n) {
            return SOCK_WRITEERROR;
        }
        Tcl_DStringSetLength(bufPtr, 0);
    }
#endif
    if (sockPtr->tfd > 0) {
        buf.iov_base = tbuf;
        buf.iov_len = MIN(nread, sizeof(tbuf));
    } else {
        Tcl_DStringSetLength(bufPtr, (int)(buflen + nread));
        buf.iov_base = bufPtr->string + reqPtr->woff;
        buf.iov_len = nread;
    }

    if (reqPtr->leftover > 0u) {


        n = (ssize_t)reqPtr->leftover;
        reqPtr->leftover = 0u;
        buflen = 0u;
        Ns_Log(DriverDebug, "SockRead receive from leftover %" PRIdz " bytes", n);
    } else {


        n = NsDriverRecv(sockPtr, &buf, 1, NULL);
        Ns_Log(DriverDebug, "SockRead receive from network %" PRIdz " bytes sockState %.2x",
               n, (int)sockPtr->recvSockState);
    }

    {
        Ns_SockState nsSockState = sockPtr->recvSockState;


        switch (nsSockState) {
        case NS_SOCK_TIMEOUT:  NS_FALL_THROUGH;
        case NS_SOCK_EXCEPTION:
            return SOCK_READERROR;
        case NS_SOCK_AGAIN:
            Tcl_DStringSetLength(bufPtr, (int)buflen);
            return SOCK_MORE;
        case NS_SOCK_DONE:
            return SOCK_CLOSE;
        case NS_SOCK_READ:
            break;

        case NS_SOCK_CANCEL:  NS_FALL_THROUGH;
        case NS_SOCK_EXIT:    NS_FALL_THROUGH;
        case NS_SOCK_INIT:    NS_FALL_THROUGH;
        case NS_SOCK_WRITE:
            Ns_Log(Warning, "SockRead received unexpected state %.2x from driver", nsSockState);
            return SOCK_READERROR;

        case NS_SOCK_NONE:


            if (n < 0) {
                Tcl_DStringSetLength(bufPtr, (int)buflen);


                if (errno == 0) {
                    return SOCK_CLOSE;
                }
                return SOCK_READERROR;
            }

            if (n == 0) {
                Tcl_DStringSetLength(bufPtr, (int)buflen);
                return SOCK_MORE;
            }
            break;

        }
    }

    if (sockPtr->tfd > 0) {
        if (ns_write(sockPtr->tfd, tbuf, (size_t)n) != n) {
            return SOCK_WRITEERROR;
        }
    } else {
        Tcl_DStringSetLength(bufPtr, (int)(buflen + (size_t)n));
    }

    reqPtr->woff  += (size_t)n;
    reqPtr->avail += (size_t)n;


    if ((drvPtr->opts & NS_DRIVER_NOPARSE) != 0u) {
        return SOCK_READY;
    }

    resultState = SockParse(sockPtr);

    return resultState;
}
