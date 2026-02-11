handler( int sig ){
	switch( sig ){
	case SIGALRM:
		alarm_flag = 1;
		diag( COMPONENT, DIAG_INFO,
			"received alarm: time to poll for attachment point" );
		break;
	case SIGTERM:
	case SIGSTOP:
	case SIGINT:
	case SIGKILL:
		ilmi_state = down;
		exit( 1 );
	}
    }
