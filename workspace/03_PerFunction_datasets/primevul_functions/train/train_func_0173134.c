WriterPerPoolRates(WriterSock *writePtr, Tcl_HashTable *pools)
{
    WriterSock     *curPtr;
    Tcl_HashSearch  search;
    Tcl_HashEntry  *hPtr;

    NS_NONNULL_ASSERT(writePtr != NULL);
    NS_NONNULL_ASSERT(pools != NULL);


    hPtr = Tcl_FirstHashEntry(pools, &search);
    while (hPtr != NULL) {
        ConnPoolInfo *infoPtr = (ConnPoolInfo *)Tcl_GetHashValue(hPtr);
        infoPtr->currentPoolRate = 0;
        hPtr = Tcl_NextHashEntry(&search);
    }


    for (curPtr = writePtr; curPtr != NULL; curPtr = curPtr->nextPtr) {


        if (curPtr->poolPtr->rate.poolLimit > 0 && curPtr->currentRate > 0) {


            ConnPoolInfo *infoPtr = WriterGetInfoPtr(curPtr, pools);

            infoPtr->currentPoolRate += curPtr->currentRate;
            Ns_Log(DriverDebug, "poollimit pool '%s' added rate poolLimit %d poolRate %d",
                   curPtr->poolPtr->pool,
                   curPtr->poolPtr->rate.poolLimit,
                   infoPtr->currentPoolRate);
        }
    }


    hPtr = Tcl_FirstHashEntry(pools, &search);
    while (hPtr != NULL) {
        ConnPool     *poolPtr = (ConnPool *)Tcl_GetHashKey(pools, hPtr);
        int           totalPoolRate, writerThreadCount, threadDeltaRate;
        ConnPoolInfo *infoPtr;


        infoPtr = (ConnPoolInfo *)Tcl_GetHashValue(hPtr);
        totalPoolRate = NsPoolTotalRate(poolPtr,
                                        infoPtr->threadSlot,
                                        infoPtr->currentPoolRate,
                                        &writerThreadCount);


        if (infoPtr->currentPoolRate == 0) {
            threadDeltaRate = (poolPtr->rate.poolLimit - totalPoolRate);
        } else {
            threadDeltaRate = (poolPtr->rate.poolLimit - totalPoolRate) / writerThreadCount;
        }
        infoPtr->deltaPercentage = threadDeltaRate / 10;
        if (infoPtr->deltaPercentage < -50) {
            infoPtr->deltaPercentage = -50;
        }

        if (totalPoolRate > 0) {
            Ns_Log(Notice, "... pool '%s' thread's pool rate %d total pool rate %d limit %d "
                   "(#%d writer threads) -> computed rate %d (%d%%) ",
                   NsPoolName(poolPtr->pool),
                   infoPtr->currentPoolRate,
                   totalPoolRate,
                   poolPtr->rate.poolLimit,
                   writerThreadCount,
                   threadDeltaRate,
                   infoPtr->deltaPercentage
                   );
        }

        hPtr = Tcl_NextHashEntry(&search);
    }
}
