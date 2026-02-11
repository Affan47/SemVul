firm_bribe()
{
	err_when( id != MSG_FIRM_BRIBE);

	short *shortPtr = (short *)data_buf;


	Firm *firmPtr;
	if( validate_firm(*shortPtr, 1) && !spy_array.is_deleted(shortPtr[1])
		&& (firmPtr = firm_array[*shortPtr])
		&& (shortPtr[2] == 0 && firmPtr->overseer_recno ||
			shortPtr[2] >= 1 && shortPtr[2] <= firm_array[*shortPtr]->worker_count) )

	{
#ifdef DEBUG_LONG_LOG
		long_log->printf("firm %d, spy %d briber worker %d\n", shortPtr[0], shortPtr[1], shortPtr[2]);
#endif
		firm_array[*shortPtr]->spy_bribe(shortPtr[3], shortPtr[1], shortPtr[2]);
	}
}
