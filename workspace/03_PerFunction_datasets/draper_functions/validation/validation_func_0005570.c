runAgentWorkLoop(DUL_NETWORKKEY ** networkKey,
		 DMAN_HANDLE ** dmanHandle, IDB_HANDLE ** idbHandle,
		 FIS_HANDLE ** fisHandle)
{
    LST_HEAD *workList;
    FIS_WORKQUEUERECORD *workQueue;
    CTNBOOLEAN done = FALSE;
    CONDITION cond;
    DUL_ASSOCIATIONKEY *associationKey;
    DUL_ASSOCIATESERVICEPARAMETERS params;

    workList = LST_Create();
    if (workList == NULL) {
	fprintf(stderr, "Could not create an initial work list. Exiting now.\n");
	return;
    }
    while (!done) {
	cond = FIS_GetWorkQueue(fisHandle, FIS_WQ_STORAGECOMMIT, NULL, 1,
				workList);
	if (cond != FIS_NORMAL) {
	    COND_DumpConditions();
	    cleanupWorkList(&workList);
	    return;
	}
	while ((workQueue = LST_Dequeue(&workList)) != NULL) {
	    printf("%s %s\n", workQueue->TasNam, workQueue->TasID);

	    cond = establishCommitResultAssociation(workQueue->TasID,
						networkKey, &associationKey,
					    &params, dmanHandle, fisHandle);
	    if (cond == APP_NORMAL)
		cond = processStorageCommitRequest(workQueue->TasID,
						   &associationKey, &params,
						   idbHandle, fisHandle);
	    (void) DUL_ReleaseAssociation(&associationKey);
	    if (cond == APP_NORMAL) {
		cond = FIS_DeleteWorkQueueRecord(fisHandle, workQueue->TasID);
		if (cond != FIS_NORMAL) {
		    COND_DumpConditions();
		    cleanupWorkList(&workList);
		    free(workQueue);
		    return;
		}
	    } else {
		COND_DumpConditions();
		free(workQueue);
	    }
	}
#ifdef _MSC_VER
	Sleep(15);
#else
	sleep(15);
#endif
    }
    cleanupWorkList(&workList);
}
