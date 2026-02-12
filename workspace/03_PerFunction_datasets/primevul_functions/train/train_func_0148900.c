zone_load(dns_zone_t *zone, unsigned int flags, bool locked) {
	isc_result_t result;
	isc_time_t now;
	isc_time_t loadtime;
	dns_db_t *db = NULL;
	bool rbt, hasraw;

	REQUIRE(DNS_ZONE_VALID(zone));

	if (!locked)
		LOCK_ZONE(zone);

	INSIST(zone != zone->raw);
	hasraw = inline_secure(zone);
	if (hasraw) {


		result = zone_load(zone->raw, flags, false);
		if (result != ISC_R_SUCCESS) {
			if (!locked)
				UNLOCK_ZONE(zone);
			return(result);
		}
		LOCK_ZONE(zone->raw);
	}

	TIME_NOW(&now);

	INSIST(zone->type != dns_zone_none);

	if (DNS_ZONE_FLAG(zone, DNS_ZONEFLG_LOADING)) {
		if ((flags & DNS_ZONELOADFLAG_THAW) != 0)
			DNS_ZONE_SETFLAG(zone, DNS_ZONEFLG_THAW);
		result = DNS_R_CONTINUE;
		goto cleanup;
	}

	INSIST(zone->db_argc >= 1);

	rbt = strcmp(zone->db_argv[0], "rbt") == 0 ||
	      strcmp(zone->db_argv[0], "rbt64") == 0;

	if (zone->db != NULL && zone->masterfile == NULL && rbt) {


		result = ISC_R_SUCCESS;
		goto cleanup;
	}

	if (zone->db != NULL && dns_zone_isdynamic(zone, false)) {


		if (zone->type == dns_zone_master && !hasraw)
			result = DNS_R_DYNAMIC;
		else
			result = ISC_R_SUCCESS;
		goto cleanup;
	}


	TIME_NOW(&loadtime);


	if (zone->masterfile != NULL) {
		isc_time_t filetime;


		if (!isc_time_isepoch(&zone->loadtime) &&
		    (flags & DNS_ZONELOADFLAG_NOSTAT) != 0) {
			result = ISC_R_SUCCESS;
			goto cleanup;
		}

		if (DNS_ZONE_FLAG(zone, DNS_ZONEFLG_LOADED) &&
		    !zone_touched(zone))
		{
			dns_zone_logc(zone, DNS_LOGCATEGORY_ZONELOAD,
				      ISC_LOG_DEBUG(1),
				      "skipping load: master file "
				      "older than last load");
			result = DNS_R_UPTODATE;
			goto cleanup;
		}


		result = isc_file_getmodtime(zone->masterfile, &filetime);
		if (result == ISC_R_SUCCESS &&
		    isc_time_compare(&loadtime, &filetime) > 0)
			loadtime = filetime;
	}


	if (zone->type == dns_zone_master &&
	    strcmp(zone->db_argv[0], "_builtin") == 0 &&
	    (zone->db_argc < 2 || strcmp(zone->db_argv[1], "empty") != 0) &&
	    DNS_ZONE_FLAG(zone, DNS_ZONEFLG_LOADED)) {
		result = ISC_R_SUCCESS;
		goto cleanup;
	}


	if (strcmp(zone->db_argv[0], "dlz") == 0) {
		dns_dlzdb_t *dlzdb;
		dns_dlzfindzone_t findzone;

		for (dlzdb = ISC_LIST_HEAD(zone->view->dlz_unsearched);
		     dlzdb != NULL;
		     dlzdb = ISC_LIST_NEXT(dlzdb, link))
		{
			INSIST(DNS_DLZ_VALID(dlzdb));
			if (strcmp(zone->db_argv[1], dlzdb->dlzname) == 0)
				break;
		}

		if (dlzdb == NULL) {
			dns_zone_logc(zone, DNS_LOGCATEGORY_ZONELOAD,
				      ISC_LOG_ERROR,
				      "DLZ %s does not exist or is set "
				      "to 'search yes;'", zone->db_argv[1]);
			result = ISC_R_NOTFOUND;
			goto cleanup;
		}

		ZONEDB_LOCK(&zone->dblock, isc_rwlocktype_write);

		findzone = dlzdb->implementation->methods->findzone;
		result = (*findzone)(dlzdb->implementation->driverarg,
				     dlzdb->dbdata, dlzdb->mctx,
				     zone->view->rdclass, &zone->origin,
				     NULL, NULL, &db);
		if (result != ISC_R_NOTFOUND) {
			if (zone->db != NULL)
				zone_detachdb(zone);
			zone_attachdb(zone, db);
			dns_db_detach(&db);
			result = ISC_R_SUCCESS;
		}
		ZONEDB_UNLOCK(&zone->dblock, isc_rwlocktype_write);

		if (result == ISC_R_SUCCESS) {
			if (dlzdb->configure_callback == NULL)
				goto cleanup;

			result = (*dlzdb->configure_callback)(zone->view,
							      dlzdb, zone);
			if (result != ISC_R_SUCCESS)
				dns_zone_logc(zone, DNS_LOGCATEGORY_ZONELOAD,
					      ISC_LOG_ERROR,
					      "DLZ configuration callback: %s",
					      isc_result_totext(result));
		}
		goto cleanup;
	}

	if ((zone->type == dns_zone_slave || zone->type == dns_zone_mirror ||
	     zone->type == dns_zone_stub ||
	     (zone->type == dns_zone_redirect && zone->masters != NULL)) &&
	    rbt) {
		if (zone->masterfile == NULL ||
		    !isc_file_exists(zone->masterfile)) {
			if (zone->masterfile != NULL) {
				dns_zone_logc(zone, DNS_LOGCATEGORY_ZONELOAD,
					      ISC_LOG_DEBUG(1),
					     "no master file");
			}
			zone->refreshtime = now;
			if (zone->task != NULL)
				zone_settimer(zone, &now);
			result = ISC_R_SUCCESS;
			goto cleanup;
		}
	}

	dns_zone_logc(zone, DNS_LOGCATEGORY_ZONELOAD,
		      ISC_LOG_DEBUG(1), "starting load");

	result = dns_db_create(zone->mctx, zone->db_argv[0],
			       &zone->origin, (zone->type == dns_zone_stub) ?
			       dns_dbtype_stub : dns_dbtype_zone,
			       zone->rdclass,
			       zone->db_argc - 1, zone->db_argv + 1,
			       &db);

	if (result != ISC_R_SUCCESS) {
		dns_zone_logc(zone, DNS_LOGCATEGORY_ZONELOAD, ISC_LOG_ERROR,
			     "loading zone: creating database: %s",
			     isc_result_totext(result));
		goto cleanup;
	}
	dns_db_settask(db, zone->task);

	if (zone->type == dns_zone_master || zone->type == dns_zone_slave ||
	    zone->type == dns_zone_mirror)
	{
		result = dns_db_setgluecachestats(db, zone->gluecachestats);
		if (result == ISC_R_NOTIMPLEMENTED) {
			result = ISC_R_SUCCESS;
		}
		if (result != ISC_R_SUCCESS) {
			goto cleanup;
		}
	}

	if (! dns_db_ispersistent(db)) {
		if (zone->masterfile != NULL) {
			result = zone_startload(db, zone, loadtime);
		} else {
			result = DNS_R_NOMASTERFILE;
			if (zone->type == dns_zone_master ||
			    (zone->type == dns_zone_redirect &&
			     zone->masters == NULL)) {
				dns_zone_logc(zone, DNS_LOGCATEGORY_ZONELOAD,
					      ISC_LOG_ERROR,
					     "loading zone: "
					     "no master file configured");
				goto cleanup;
			}
			dns_zone_logc(zone, DNS_LOGCATEGORY_ZONELOAD,
				      ISC_LOG_INFO, "loading zone: "
				      "no master file configured: continuing");
		}
	}

	if (result == DNS_R_CONTINUE) {
		DNS_ZONE_SETFLAG(zone, DNS_ZONEFLG_LOADING);
		if ((flags & DNS_ZONELOADFLAG_THAW) != 0)
			DNS_ZONE_SETFLAG(zone, DNS_ZONEFLG_THAW);
		goto cleanup;
	}

	result = zone_postload(zone, db, loadtime, result);

 cleanup:
	if (hasraw)
		UNLOCK_ZONE(zone->raw);
	if (!locked)
		UNLOCK_ZONE(zone);
	if (db != NULL)
		dns_db_detach(&db);
	return (result);
}
