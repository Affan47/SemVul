init_counter()
{

	m.counters [0] =     1;
	m.counters [1] =     0;
	m.counters [2] = -0x20u;
	m.counters [3] =  0x0B;

	int n = 2;
	for ( int i = 1; i < 32; i++ )
	{
		m.counter_select [i] = &m.counters [n];
		if ( !--n )
			n = 3;
	}
	m.counter_select [ 0] = &m.counters [0];
	m.counter_select [30] = &m.counters [2];
}
