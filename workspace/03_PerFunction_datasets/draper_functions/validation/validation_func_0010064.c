fs2netd_login_do()
{
	if (Multi_tracker_id < 0) {
		if ( Is_standalone && std_gen_is_active() ) {
			std_gen_set_text("Verifying username and password", 1);
		} else {
			popup_change_text( XSTR("Verifying username and password", 1576) );
		}

		memset(Multi_tracker_id_string, 0, sizeof(Multi_tracker_id_string));

		if (Local_timeout == -1) {
			Local_timeout = timer_get_seconds() + 15;
		}


		if ( timer_get_seconds() > Local_timeout ) {
			ml_string("FS2NetD MSG: Login failure due to timeout!");
			Local_timeout = -1;
			return 2;
		}

		const char *user = Multi_tracker_login;
		const char *passwd = Multi_tracker_passwd;

		if (Is_standalone) {
			if ( strlen(Multi_options_g.std_pxo_login) ) {
				user = Multi_options_g.std_pxo_login;
			}

			if ( strlen(Multi_options_g.std_pxo_password) ) {
				passwd = Multi_options_g.std_pxo_password;
			}
		}

		Multi_tracker_id = FS2NetD_Login(user, passwd, do_full_packet);


		do_full_packet = false;


		if (Multi_tracker_id == -2) {
			Multi_tracker_id = -1;
			Local_timeout = -1;
			return 1;
		}

		if (Multi_tracker_id >= 0) {
			ml_printf("FS2NetD MSG: Login '%s' is valid, session ID is %d!", user, Multi_tracker_id);
			do_full_packet = true;
			Local_timeout = -1;
		}
	} else {
		if ( Is_standalone && std_gen_is_active() ) {
			std_gen_set_text("Getting pilot stats", 1);
		} else {
			popup_change_text( XSTR("Getting pilot stats", 1577) );
		}

		if (Local_timeout == -1) {
			Local_timeout = timer_get_seconds() + 30;
		}


		if ( timer_get_seconds() > Local_timeout ) {

			Local_timeout = -1;
			return 2;
		}

		if (do_full_packet) {
			ml_printf("FS2NetD MSG: Requesting login pilot stats for '%s' ...", Players[Player_num].callsign);
		}

		int rescode = FS2NetD_GetPlayerData(Players[Player_num].callsign, &Players[Player_num], true, do_full_packet);

		do_full_packet = false;

		if ( rescode != -1 ) {
			Local_timeout = -1;
			return (rescode + 3);
		}
	}

	return 0;
}
