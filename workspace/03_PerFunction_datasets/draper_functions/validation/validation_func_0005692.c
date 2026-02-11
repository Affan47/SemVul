endElement( const QString &, const QString &, const QString & )
{
	switch ( _state ) {
	case StateHeight:
		_state = StateDocument;
		break;
	case StateWidth:
		_state = StateDocument;
		break;
	case StateTile:
		_state = StateDocument;
		_list->append( _model );
		break;
	case StateName:
		_state = StateTile;
		break;
	case StateCoeff:
		_state = StateTile;
		break;
	case StateColor:
		_model->setColor( QColor( _red, _green, _blue ) );
		_state = StateTile;
		break;
	case StateColorRed:
		_state = StateColor;
		break;
	case StateColorGreen:
		_state = StateColor;
		break;
	case StateColorBlue:
		_state = StateColor;
		break;
	case StateDiversification:
		_state = StateTile;
		break;
	default:

		break;
    }
    return true;
}
