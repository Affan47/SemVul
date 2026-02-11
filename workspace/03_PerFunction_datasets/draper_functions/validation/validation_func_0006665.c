next_month()
{
	int	 i;
	Firm*  firmPtr;

	LOG_MSG("begin FirmArray::next_month");
	LOG_MSG(misc.get_random_seed());
	for(i=1; i <=size() ; i++)
	{
		firmPtr = (Firm*)get_ptr(i);

		if( firmPtr && !firmPtr->under_construction )
		{
			LOG_MSG("Firm next_month");
			LOG_MSG( i );
			firmPtr->next_month();
			LOG_MSG(misc.get_random_seed());
		}
	}
	LOG_MSG("end FirmArray::next_month");
	LOG_MSG(misc.get_random_seed());
}
