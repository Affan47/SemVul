generatePrime( u64 minimum )
{
	if( minimum < 2 )
	{
		Value = 2;
		return Value;
	}

	for (u64 i = minimum; i >= minimum; i++)
	{
		bool isprime = true;

		u64 root = ceil(sqrt(i));

		for (u64 j = 2; j < root; j++)
		{
			if( dMod(i,j) == 0 )
			{
				isprime = false;
				j = root;
			}
		}

		if( isprime == true )
		{
			if( i > minimum )
			{
				Value = i;
				return i;
			}
		}
	}

	return 0;
}
