void check_reload(time_t t)
{
	time_t printcap_cache_time = (time_t)lp_printcap_cache_time();

	if(last_smb_conf_reload_time == 0) {
		last_smb_conf_reload_time = t;


		if ( printcap_cache_time > 60 )
			last_printer_reload_time = t - printcap_cache_time + 60;
		else
			last_printer_reload_time = t;
	}

	if (mypid != getpid()) {


		int time_range = 60;

		last_printer_reload_time += random() % time_range;
		mypid = getpid();
	}

	if (t >= last_smb_conf_reload_time+SMBD_RELOAD_CHECK) {
		reload_services(True);
		last_smb_conf_reload_time = t;
	}


	if ( printcap_cache_time != 0 )
	{


		if ( (t >= last_printer_reload_time+printcap_cache_time)
			|| (t-last_printer_reload_time  < 0) )
		{
			DEBUG( 3,( "Printcap cache time expired.\n"));
			reload_printers();
			last_printer_reload_time = t;
		}
	}
}
