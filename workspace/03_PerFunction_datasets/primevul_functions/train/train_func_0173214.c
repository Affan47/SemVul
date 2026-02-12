NsGetRequest(Sock *sockPtr, const Ns_Time *nowPtr)
{
    Request *reqPtr;

    NS_NONNULL_ASSERT(sockPtr != NULL);


    reqPtr = sockPtr->reqPtr;

    if (likely(reqPtr != NULL)) {

        if (likely(reqPtr->request.line != NULL)) {
            Ns_Log(DriverDebug, "NsGetRequest got the pre-parsed request <%s> from the driver",
                   reqPtr->request.line);

        } else if (sockPtr->drvPtr->requestProc == NULL) {


            SockState status;

            Ns_Log(DriverDebug, "NsGetRequest has to read+parse the request");


            do {
                Ns_Log(DriverDebug, "NsGetRequest calls SockRead");
                status = SockRead(sockPtr, 0, nowPtr);
            } while (status == SOCK_MORE);


            if (status != SOCK_READY) {
                if (sockPtr->reqPtr != NULL) {
                    Ns_Log(DriverDebug, "NsGetRequest calls RequestFree");
                    RequestFree(sockPtr);
                }
                reqPtr = NULL;
            }
        } else {
            Ns_Log(DriverDebug, "NsGetRequest found driver specific request Proc, "
                   "probably from a non-HTTP driver");
        }
    } else {
        Ns_Log(DriverDebug, "NsGetRequest has reqPtr NULL");
    }

    return reqPtr;
}
