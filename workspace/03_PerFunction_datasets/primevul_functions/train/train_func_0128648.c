read_pool( byte *buffer, size_t length, int level )
{
    int i;
    ulong *sp, *dp;

    if( length > POOLSIZE ) {
	log_bug("too many random bits requested\n");
    }

    if( !pool_filled ) {
	if( read_seed_file() )
	    pool_filled = 1;
    }


    if( level == 2 && !did_initial_extra_seeding ) {
	size_t needed;

	pool_balance = 0;
	needed = length - pool_balance;
	if( needed < POOLSIZE/2 )
	    needed = POOLSIZE/2;
	else if( needed > POOLSIZE )
	    BUG();
	read_random_source( 3, needed, 2 );
	pool_balance += needed;
	did_initial_extra_seeding=1;
    }


    if( level == 2 && pool_balance < length ) {
	size_t needed;

	if( pool_balance < 0 )
	    pool_balance = 0;
	needed = length - pool_balance;
	if( needed > POOLSIZE )
	    BUG();
	read_random_source( 3, needed, 2 );
	pool_balance += needed;
    }


    while( !pool_filled )
	random_poll();


    fast_random_poll();

    if( !level ) {

	for(i=0,dp=(ulong*)keypool, sp=(ulong*)rndpool;
				    i < POOLWORDS; i++, dp++, sp++ )
	    *dp = *sp + ADD_VALUE;

	mix_pool(rndpool); rndstats.mixrnd++;
	mix_pool(keypool); rndstats.mixkey++;
	memcpy( buffer, keypool, length );
    }
    else {

	if( !just_mixed ) {
	    mix_pool(rndpool);
	    rndstats.mixrnd++;
	}

	for(i=0,dp=(ulong*)keypool, sp=(ulong*)rndpool;
				    i < POOLWORDS; i++, dp++, sp++ )
	    *dp = *sp + ADD_VALUE;

	mix_pool(rndpool); rndstats.mixrnd++;
	mix_pool(keypool); rndstats.mixkey++;


	while( length-- ) {
	    *buffer++ = keypool[pool_readpos++];
	    if( pool_readpos >= POOLSIZE )
		pool_readpos = 0;
	    pool_balance--;
	}
	if( pool_balance < 0 )
	    pool_balance = 0;

	wipememory(keypool, POOLSIZE);
    }
}
