sSquare( u64 base, u64 exponent, u64 modulo )
{


	u64 maxBinary = 0;
	u32 flag, i=0;

	for(i=0; i<32; i++)
	{
		flag = 1<<i;

		if( (exponent) & flag )
		{
			maxBinary = i;
		}
	}

	std::vector<u64> powerList;

	u64 value = base;

	powerList.push_back( value );


	for(i=1; i<= maxBinary; i++)
	{

		value = dMod((value * value), modulo);

		powerList.push_back(value);
	}


	value = 1;

	for(i=0; i<32; i++)
	{
		flag = 1 << i;

		if( exponent & flag )
		{
			value = dMod((value * powerList[i]), modulo);
		}
	}


	return value;
}
