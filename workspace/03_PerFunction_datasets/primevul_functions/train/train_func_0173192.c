RequestNew(Sock *sockPtr)
{
    Request *reqPtr;
    bool     reuseRequest = NS_TRUE;

    NS_NONNULL_ASSERT(sockPtr != NULL);


    Ns_MutexLock(&reqLock);
    reqPtr = firstReqPtr;
    if (likely(reqPtr != NULL)) {
        firstReqPtr = reqPtr->nextPtr;
    } else {
        reuseRequest = NS_FALSE;
    }
    Ns_MutexUnlock(&reqLock);

    if (reuseRequest) {
        Ns_Log(DriverDebug, "RequestNew reuses a Request");
    }


    if (reqPtr == NULL) {
        Ns_Log(DriverDebug, "RequestNew gets a fresh Request");
        reqPtr = ns_calloc(1u, sizeof(Request));
        Tcl_DStringInit(&reqPtr->buffer);
        reqPtr->headers = Ns_SetCreate(NULL);
    }
    sockPtr->reqPtr = reqPtr;
}
