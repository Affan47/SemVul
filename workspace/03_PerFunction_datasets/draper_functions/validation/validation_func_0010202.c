gb_series_parse (gchar *string, gbSeries *series)
{


	if ( string == NULL ) {
		return GB_ERROR_PARSE_SERIES_NULL;
	}
	if ( !string[0] ) {
		return GB_ERROR_PARSE_SERIES_EMPTY;
	}


	string[0] = toupper( string[0] );
	switch ( string[0] ) {

	case 'E':
		string[1] = toupper( string[1] );
		switch ( string[1] ) {
		case 0:
			*series = GB_SERIES_E;
			break;
		case 'E':
			if ( string[2] == 0 ) {
				*series = GB_SERIES_EE;
			}
			else {
				return GB_ERROR_PARSE_SERIES_BAD_SERIES;
			}
			break;
		default:
			return GB_ERROR_PARSE_SERIES_BAD_SERIES;
			break;
		}
		break;

	case 'I':
		if ( string[1] == 0 ) {
			*series = GB_SERIES_I;
		}
		else {
			return GB_ERROR_PARSE_SERIES_BAD_SERIES;
		}
		break;

	case 'S':
		if ( string[1] == 0 ) {
			*series = GB_SERIES_S;
		}
		else {
			return GB_ERROR_PARSE_SERIES_BAD_SERIES;
		}
		break;

	default:
		return GB_ERROR_PARSE_SERIES_BAD_SERIES;
		break;
	}

	return GB_OK;
}
