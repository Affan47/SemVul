SockClose(Sock *sockPtr)
{
    Driver *drvPtr = sockPtr->drvPtr;


    if (sockPtr->connPtr != NULL) {
        FreeConn(sockPtr->connPtr);
	sockPtr->connPtr = NULL;
    }

    (void) (*drvPtr->proc)(DriverClose, (Ns_Sock *) sockPtr, NULL, 0);
    ns_sockclose(sockPtr->sock);
    sockPtr->sock = INVALID_SOCKET;
    drvPtr->stats.reads += sockPtr->nreads;
    drvPtr->stats.writes += sockPtr->nwrites;
    sockPtr->nextPtr = drvPtr->freeSockPtr;
    drvPtr->freeSockPtr = sockPtr;
    --drvPtr->nactive;
}
