void Con_DrawConsole( void ) {

	Con_CheckResize();


	switch ( clc.state ) {
	case CA_UNINITIALIZED:
	case CA_CONNECTING:
	case CA_CHALLENGING:
	case CA_CONNECTED:
	case CA_PRIMED:
	case CA_LOADING:
		if ( !con_debug->integer ) {
			return;
		}

		if ( Key_GetCatcher( ) & KEYCATCH_UI ) {
			return;
		}

		Con_DrawSolidConsole( 1.0 );
		return;

	case CA_DISCONNECTED:
		if ( !( Key_GetCatcher( ) & KEYCATCH_UI ) ) {
			Con_DrawSolidConsole( 1.0 );
			return;
		}
		break;

	case CA_ACTIVE:
		if ( con.displayFrac ) {
			if ( con_debug->integer == 2 ) {

				Con_DrawSolidConsole( con.displayFrac * 2.0f );
				return;
			}
		}

		break;


	case CA_CINEMATIC:
	default:
		break;
	}

	if ( con.displayFrac ) {
		Con_DrawSolidConsole( con.displayFrac );
	} else {
		Con_DrawNotify();
	}
}
