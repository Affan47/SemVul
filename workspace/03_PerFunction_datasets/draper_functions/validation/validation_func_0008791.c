GetNumberOfAddresses( void )
{

	if (IsActive()==false)
	{
		FillIPList();
	}

	int i = 0;

	while ( ipList[ i ]!=UNASSIGNED_SYSTEM_ADDRESS )
		i++;

	return i;


}
