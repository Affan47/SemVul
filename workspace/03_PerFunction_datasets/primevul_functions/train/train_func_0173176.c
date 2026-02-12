SockClose(Sock *sockPtr, int keep)
{
    NS_NONNULL_ASSERT(sockPtr != NULL);

    if (keep != 0) {
        bool driverKeep = DriverKeep(sockPtr);
        keep = (int)driverKeep;
    }
    if (keep == (int)NS_FALSE) {
        DriverClose(sockPtr);
    }
    Ns_MutexLock(&sockPtr->drvPtr->lock);
    sockPtr->keep = (bool)keep;
    Ns_MutexUnlock(&sockPtr->drvPtr->lock);


    if (sockPtr->tfile != NULL) {
        unlink(sockPtr->tfile);
        ns_free(sockPtr->tfile);
        sockPtr->tfile = NULL;

        if (sockPtr->tfd > 0) {


            (void) ns_close(sockPtr->tfd);
        }
        sockPtr->tfd = 0;

    } else if (sockPtr->tfd > 0) {


        Ns_ReleaseTemp(sockPtr->tfd);
        sockPtr->tfd = 0;
    }

#ifndef _WIN32


    if (sockPtr->taddr != NULL) {
        munmap(sockPtr->taddr, (size_t)sockPtr->tsize);
        sockPtr->taddr = NULL;
    }
#endif
}
