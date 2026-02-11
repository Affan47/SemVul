removeLord( GenericLord * lord )
{
	_theLords.removeAll( lord );
	if( _selectedLord == lord ) {
		_selectedLord = 0;
	}
}
