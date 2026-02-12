SockAccept(Driver *drvPtr, NS_SOCKET sock, Sock **sockPtrPtr, const Ns_Time *nowPtr)
{
    Sock    *sockPtr;
    SockState sockStatus;
    NS_DRIVER_ACCEPT_STATUS status;

    NS_NONNULL_ASSERT(drvPtr != NULL);

    sockPtr = SockNew(drvPtr);


    status = DriverAccept(sockPtr, sock);

    if (unlikely(status == NS_DRIVER_ACCEPT_ERROR)) {
        sockStatus = SOCK_ERROR;


        Ns_MutexLock(&drvPtr->lock);
        sockPtr->nextPtr = drvPtr->sockPtr;
        drvPtr->sockPtr = sockPtr;
        Ns_MutexUnlock(&drvPtr->lock);
        sockPtr = NULL;

    } else {
        sockPtr->acceptTime = *nowPtr;
        drvPtr->queuesize++;

        if (status == NS_DRIVER_ACCEPT_DATA) {


            if ((drvPtr->opts & NS_DRIVER_ASYNC) != 0u) {
                sockStatus = SockRead(sockPtr, 0, nowPtr);
                if ((int)sockStatus < 0) {
                    Ns_Log(DriverDebug, "SockRead returned error %s",
                           GetSockStateName(sockStatus));

                    SockRelease(sockPtr, sockStatus, errno);
                    sockStatus = SOCK_ERROR;
                    sockPtr = NULL;
                }
            } else {


                sockStatus = SOCK_READY;
            }
        } else if (status == NS_DRIVER_ACCEPT_QUEUE) {


            if (sockPtr->reqPtr == NULL) {
                RequestNew(sockPtr);
            }
            sockStatus = SOCK_READY;
        } else {
            sockStatus = SOCK_MORE;
        }
    }

    *sockPtrPtr = sockPtr;

    return sockStatus;
}
