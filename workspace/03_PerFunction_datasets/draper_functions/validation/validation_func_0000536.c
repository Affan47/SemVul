computeBuyCreatureMax( Creature * creature )
{
	int ret = -1;

	for( int i = 0; i < DataTheme.resources.count(); i++ ) {
		if( creature->getCost( i ) >  0 ) {
			int temp = _ress->getValue( i ) / creature->getCost( i );
			if( ( ret == -1 ) || ( temp < ret ) ) {
				ret = temp;
			}
		}
	}

	if( ret == -1 ) {
		ret = 0;
	}

	return (uint)ret;
}
