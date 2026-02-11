StartTransactionCommand(void)
{
	TransactionState s = CurrentTransactionState;

	switch (s->blockState)
	{


		case TBLOCK_DEFAULT:
			StartTransaction();
			s->blockState = TBLOCK_STARTED;
			break;


		case TBLOCK_INPROGRESS:
		case TBLOCK_SUBINPROGRESS:
			break;


		case TBLOCK_ABORT:
		case TBLOCK_SUBABORT:
			break;


		case TBLOCK_STARTED:
		case TBLOCK_BEGIN:
		case TBLOCK_SUBBEGIN:
		case TBLOCK_END:
		case TBLOCK_SUBEND:
		case TBLOCK_ABORT_END:
		case TBLOCK_SUBABORT_END:
		case TBLOCK_ABORT_PENDING:
		case TBLOCK_SUBABORT_PENDING:
		case TBLOCK_SUBRESTART:
		case TBLOCK_SUBABORT_RESTART:
		case TBLOCK_PREPARE:
			elog(ERROR, "StartTransactionCommand: unexpected state %s",
				 BlockStateAsString(s->blockState));
			break;
	}


	Assert(CurTransactionContext != NULL);
	MemoryContextSwitchTo(CurTransactionContext);
}
