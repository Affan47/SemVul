AbortSubTransaction(void)
{
	TransactionState s = CurrentTransactionState;


	HOLD_INTERRUPTS();


	AtSubAbort_Memory();
	AtSubAbort_ResourceOwner();


	LWLockReleaseAll();

	AbortBufferIO();
	UnlockBuffers();

	LockWaitCancel();


	ShowTransactionState("AbortSubTransaction");

	if (s->state != TRANS_INPROGRESS)
		elog(WARNING, "AbortSubTransaction while in %s state",
			 TransStateAsString(s->state));

	s->state = TRANS_ABORT;


	SetUserIdAndSecContext(s->prevUser, s->prevSecContext);


	if (s->curTransactionOwner)
	{
		AfterTriggerEndSubXact(false);
		AtSubAbort_Portals(s->subTransactionId,
						   s->parent->subTransactionId,
						   s->parent->curTransactionOwner);
		AtEOSubXact_LargeObject(false, s->subTransactionId,
								s->parent->subTransactionId);
		AtSubAbort_Notify();
		AtEOSubXact_UpdateFlatFiles(false, s->subTransactionId,
									s->parent->subTransactionId);


		(void) RecordTransactionAbort(true);


		if (TransactionIdIsValid(s->transactionId))
			AtSubAbort_childXids();

		CallSubXactCallbacks(SUBXACT_EVENT_ABORT_SUB, s->subTransactionId,
							 s->parent->subTransactionId);

		ResourceOwnerRelease(s->curTransactionOwner,
							 RESOURCE_RELEASE_BEFORE_LOCKS,
							 false, false);
		AtEOSubXact_RelationCache(false, s->subTransactionId,
								  s->parent->subTransactionId);
		AtEOSubXact_Inval(false);
		AtSubAbort_smgr();
		ResourceOwnerRelease(s->curTransactionOwner,
							 RESOURCE_RELEASE_LOCKS,
							 false, false);
		ResourceOwnerRelease(s->curTransactionOwner,
							 RESOURCE_RELEASE_AFTER_LOCKS,
							 false, false);

		AtEOXact_GUC(false, s->gucNestLevel);
		AtEOSubXact_SPI(false, s->subTransactionId);
		AtEOSubXact_on_commit_actions(false, s->subTransactionId,
									  s->parent->subTransactionId);
		AtEOSubXact_Namespace(false, s->subTransactionId,
							  s->parent->subTransactionId);
		AtEOSubXact_Files(false, s->subTransactionId,
						  s->parent->subTransactionId);
		AtEOSubXact_HashTables(false, s->nestingLevel);
		AtEOSubXact_PgStat(false, s->nestingLevel);
	}


	XactReadOnly = s->prevXactReadOnly;

	RESUME_INTERRUPTS();
}
