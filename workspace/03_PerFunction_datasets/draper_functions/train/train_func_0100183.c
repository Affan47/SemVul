date2timestamp(DateADT dateVal)
{
	Timestamp	result;

	if (DATE_IS_NOBEGIN(dateVal))
		TIMESTAMP_NOBEGIN(result);
	else if (DATE_IS_NOEND(dateVal))
		TIMESTAMP_NOEND(result);
	else
	{
#ifdef HAVE_INT64_TIMESTAMP

		result = dateVal * USECS_PER_DAY;

		if (result / USECS_PER_DAY != dateVal)
			ereport(ERROR,
					(errcode(ERRCODE_DATETIME_VALUE_OUT_OF_RANGE),
					 errmsg("date out of range for timestamp")));
#else

		result = dateVal * (double) SECS_PER_DAY;
#endif
	}

	return result;
}
