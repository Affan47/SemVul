CreatePool(char *name)
{
    Pool *poolPtr;
    Tcl_HashEntry *hPtr;
    int new;

    hPtr = Tcl_CreateHashEntry(&pools, name, &new);
    if (!new) {
	poolPtr = Tcl_GetHashValue(hPtr);
    } else {
    	poolPtr = ns_calloc(sizeof(Pool), 1);
    	Ns_MutexInit(&poolPtr->lock);
        Ns_MutexSetName(&poolPtr->lock, "ns:pools");
    	Ns_CondInit(&poolPtr->cond);
    	Tcl_SetHashValue(hPtr, poolPtr);
    	poolPtr->name = Tcl_GetHashKey(&pools, hPtr);
    	poolPtr->threads.min = 0;
    	poolPtr->threads.max = 10;
    	poolPtr->threads.timeout = 120;
    	poolPtr->threads.maxconns = 0;
    	poolPtr->threads.spread = 20;
   }
    return poolPtr;
}
