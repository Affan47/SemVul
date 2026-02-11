rts_evalStableIO ( Capability **cap,
                        HsStablePtr s,
                          HsStablePtr *ret)
{
    StgTSO* tso;
    StgClosure *p, *r;
    SchedulerStatus stat;

    p = (StgClosure *)deRefStablePtr(s);
    tso = createStrictIOThread(*cap, RtsFlags.GcFlags.initialStkSize, p);


    tso->flags |= TSO_BLOCKEX | TSO_INTERRUPTIBLE;
    scheduleWaitThread(tso,&r,cap);
    stat = rts_getSchedStatus(*cap);

    if (stat == Success && ret != NULL) {
	ASSERT(r != NULL);
	*ret = getStablePtr((StgPtr)r);
    }
}
