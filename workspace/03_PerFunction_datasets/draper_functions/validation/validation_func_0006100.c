giveNumRace( const QString & race )
{
	int ret = 0, cpt = 0;

	QListIterator<Race *> iteRace( *this );
	while( iteRace.hasNext() ) {
		if( iteRace.next()->getName() == race ) {
			ret = cpt;
		}
		cpt++;
	}

	return ret;
}
