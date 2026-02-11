ReaderThread(void *arg)
{
    Driver *drvPtr = arg;
    Sock *sockPtr;

    ThreadName(drvPtr, "reader");
    Ns_MutexLock(&drvPtr->lock);
    while (1) {
        while (!(drvPtr->flags & DRIVER_SHUTDOWN)
                && drvPtr->readSockPtr == NULL) {
            Ns_CondWait(&drvPtr->cond, &drvPtr->lock);
    	}
        sockPtr = drvPtr->readSockPtr;
	if (sockPtr == NULL) {
	    break;
	}
        drvPtr->readSockPtr = sockPtr->nextPtr;
        if (drvPtr->readSockPtr != NULL) {
	    Ns_CondSignal(&drvPtr->cond);
	}
	--drvPtr->idlereaders;
	Ns_MutexUnlock(&drvPtr->lock);


	do {
	    SockRead(sockPtr);
        } while (sockPtr->state == SOCK_READWAIT);


	Ns_MutexLock(&drvPtr->lock);
        sockPtr->nextPtr = drvPtr->runSockPtr;
        drvPtr->runSockPtr = sockPtr;
        TriggerDriver(drvPtr);
	++drvPtr->idlereaders;
    }
    Ns_MutexUnlock(&drvPtr->lock);
    Ns_Log(Notice, "exiting");
}
