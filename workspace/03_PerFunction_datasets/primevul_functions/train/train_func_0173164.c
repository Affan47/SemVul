SockQueue(Sock *sockPtr, const Ns_Time *timePtr)
{
    Ns_ReturnCode result;

    NS_NONNULL_ASSERT(sockPtr != NULL);


    assert(sockPtr->reqPtr != NULL);

    SockSetServer(sockPtr);
    assert(sockPtr->servPtr != NULL);


    if (!NsQueueConn(sockPtr, timePtr)) {
        result = NS_TIMEOUT;
    } else {
        result = NS_OK;
    }

    return result;
}
