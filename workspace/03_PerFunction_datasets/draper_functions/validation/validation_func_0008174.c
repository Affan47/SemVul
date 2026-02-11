CloseDownFileDescriptor(OsCommPtr oc)
{
    int connection = oc->fd;

    close(connection);
    FreeOsBuffers(oc);
    BITCLEAR(AllSockets, connection);
    BITCLEAR(AllClients, connection);
#ifdef SERVER_LOCALCONN
    BITCLEAR(AllStreams, connection);
#endif
    BITCLEAR(ClientsWithInput, connection);
    BITCLEAR(GrabImperviousClients, connection);
    if (GrabInProgress) {
        BITCLEAR(SavedAllSockets, connection);
        BITCLEAR(SavedAllClients, connection);
        BITCLEAR(SavedClientsWithInput, connection);
    }
    BITCLEAR(ClientsWriteBlocked, connection);
    if (!ANYSET(ClientsWriteBlocked))
        AnyClientsWriteBlocked = FALSE;
    BITCLEAR(OutputPending, connection);
    xfree(oc);
}
