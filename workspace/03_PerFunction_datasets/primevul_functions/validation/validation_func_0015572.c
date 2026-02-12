HttpStateData::readReply(const CommIoCbParams &io)
{
    Must(!flags.do_next_read);
    flags.do_next_read = false;

    debugs(11, 5, io.conn);


    if (io.flag == Comm::ERR_CLOSING) {
        debugs(11, 3, "http socket closing");
        return;
    }

    if (EBIT_TEST(entry->flags, ENTRY_ABORTED)) {
        abortTransaction("store entry aborted while reading reply");
        return;
    }

    Must(Comm::IsConnOpen(serverConnection));
    Must(io.conn->fd == serverConnection->fd);


    Must(maybeMakeSpaceAvailable(true));
    CommIoCbParams rd(this);
    rd.conn = io.conn;
    rd.size = entry->bytesWanted(Range<size_t>(0, inBuf.spaceSize()));

    if (rd.size <= 0) {
        assert(entry->mem_obj);
        AsyncCall::Pointer nilCall;
        entry->mem_obj->delayRead(DeferredRead(readDelayed, this, CommRead(io.conn, NULL, 0, nilCall)));
        return;
    }

    switch (Comm::ReadNow(rd, inBuf)) {
    case Comm::INPROGRESS:
        if (inBuf.isEmpty())
            debugs(33, 2, io.conn << ": no data to process, " << xstrerr(rd.xerrno));
        flags.do_next_read = true;
        maybeReadVirginBody();
        return;

    case Comm::OK:
    {
        payloadSeen += rd.size;
#if USE_DELAY_POOLS
        DelayId delayId = entry->mem_obj->mostBytesAllowed();
        delayId.bytesIn(rd.size);
#endif

        statCounter.server.all.kbytes_in += rd.size;
        statCounter.server.http.kbytes_in += rd.size;
        ++ IOStats.Http.reads;

        int bin = 0;
        for (int clen = rd.size - 1; clen; ++bin)
            clen >>= 1;

        ++ IOStats.Http.read_hist[bin];

        request->hier.notePeerRead();
    }


    break;

    case Comm::ENDFILE:
        eof = 1;
        flags.do_next_read = false;


        break;


    default:
        debugs(11, 2, io.conn << ": read failure: " << xstrerr(rd.xerrno));
        ErrorState *err = new ErrorState(ERR_READ_ERROR, Http::scBadGateway, fwd->request);
        err->xerrno = rd.xerrno;
        fwd->fail(err);
        flags.do_next_read = false;
        closeServer();
        mustStop("HttpStateData::readReply");
        return;
    }


    processReply();
}
