check( QuestData * data )
{
	bool ret = false;
	uint i, nb;

	nb = _list.count();
	if( nb ) {
		if( _compositeType == AND  ) {
			ret = true;
			for( i = 0; i < nb; i++ ) {
				ret = ret && _list.at( i )->check( data );
			}
		} else {
			ret = false;
			for( i = 0; i < nb; i++ ) {
				ret = ret || _list.at( i )->check( data );
			}
		}
	}

	return ret;
}
