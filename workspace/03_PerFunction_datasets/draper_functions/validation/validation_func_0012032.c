newDay()
{
	_day++;
	_daynum++;
	_turn++;
	if( _day > FIRST_LEVEL ) {
		_day = 1;
		_week++;
	}
	if( _week > SECOND_LEVEL ) {
		_week = 1;
		_month++;
		_daynum = 1;
	}
	if( _month > THIRD_LEVEL ) {
		_month = 1;
		_year++;
	}

	emit sig_changed();
}
