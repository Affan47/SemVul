NsStartDrivers(void)
{
    Driver *drvPtr;


    for (drvPtr = firstDrvPtr; drvPtr != NULL;  drvPtr = drvPtr->nextPtr) {

        if (drvPtr->port == 0u) {


            continue;
        }

        Ns_ThreadCreate(DriverThread, drvPtr, 0, &drvPtr->thread);
        Ns_MutexLock(&drvPtr->lock);
        while ((drvPtr->flags & DRIVER_STARTED) == 0u) {
            Ns_CondWait(&drvPtr->cond, &drvPtr->lock);
        }


        Ns_MutexUnlock(&drvPtr->lock);
    }
}
