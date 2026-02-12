detect_mysql_capabilities_for_backup()
{
	if (xtrabackup_incremental) {


		if (server_flavor == FLAVOR_MARIADB &&
		    mysql_server_version < 100106) {
			have_changed_page_bitmaps = false;
		}
	}


	if (opt_galera_info && !have_galera_enabled) {
		msg("--galera-info is specified on the command "
		 	"line, but the server does not support Galera "
		 	"replication. Ignoring the option.\n");
		opt_galera_info = false;
	}

	if (opt_slave_info && have_multi_threaded_slave &&
	    !have_gtid_slave && !opt_safe_slave_backup) {
		msg("The --slave-info option requires GTID enabled or "
			"--safe-slave-backup option used for a multi-threaded "
			"slave.\n");
		return(false);
	}

	return(true);
}
