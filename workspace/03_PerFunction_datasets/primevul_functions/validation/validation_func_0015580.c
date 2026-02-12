HttpStateData::maybeReadVirginBody()
{

    if (!Comm::IsConnOpen(serverConnection) || fd_table[serverConnection->fd].closing())
        return;

    if (!maybeMakeSpaceAvailable(false))
        return;


    if (!flags.do_next_read)
        return;

    flags.do_next_read = false;


    assert(!Comm::MonitorsRead(serverConnection->fd));


    typedef CommCbMemFunT<HttpStateData, CommIoCbParams> Dialer;
    AsyncCall::Pointer call = JobCallback(11, 5, Dialer, this, HttpStateData::readReply);
    Comm::Read(serverConnection, call);
}
