zone_maintenance(dns_zone_t *zone) {
	const char me[] = "zone_maintenance";
	isc_time_t now;
	isc_result_t result;
	bool dumping, load_pending;

	REQUIRE(DNS_ZONE_VALID(zone));
	ENTER;


	LOCK_ZONE(zone);
	load_pending = DNS_ZONE_FLAG(zone, DNS_ZONEFLG_LOADPENDING);
	UNLOCK_ZONE(zone);

	if (load_pending) {
		return;
	}


	if (zone->view == NULL || zone->view->adb == NULL)
		return;

	TIME_NOW(&now);


	switch (zone->type) {
	case dns_zone_redirect:
		if (zone->masters == NULL)
			break;

	case dns_zone_slave:
	case dns_zone_mirror:
	case dns_zone_stub:
		LOCK_ZONE(zone);
		if (isc_time_compare(&now, &zone->expiretime) >= 0 &&
		    DNS_ZONE_FLAG(zone, DNS_ZONEFLG_LOADED)) {
			zone_expire(zone);
			zone->refreshtime = now;
		}
		UNLOCK_ZONE(zone);
		break;
	default:
		break;
	}


	switch (zone->type) {
	case dns_zone_redirect:
		if (zone->masters == NULL)
			break;

	case dns_zone_slave:
	case dns_zone_mirror:
	case dns_zone_stub:
		if (!DNS_ZONE_FLAG(zone, DNS_ZONEFLG_DIALREFRESH) &&
		    isc_time_compare(&now, &zone->refreshtime) >= 0)
			dns_zone_refresh(zone);
		break;
	default:
		break;
	}


	if ((zone->type == dns_zone_slave || zone->type == dns_zone_mirror) &&
	    (DNS_ZONE_FLAG(zone, DNS_ZONEFLG_NEEDNOTIFY) ||
	     DNS_ZONE_FLAG(zone, DNS_ZONEFLG_NEEDSTARTUPNOTIFY)) &&
	    isc_time_compare(&now, &zone->notifytime) >= 0)
		zone_notify(zone, &now);


	switch (zone->type) {
	case dns_zone_master:
	case dns_zone_slave:
	case dns_zone_mirror:
	case dns_zone_key:
	case dns_zone_redirect:
	case dns_zone_stub:
		LOCK_ZONE(zone);
		if (zone->masterfile != NULL &&
		    isc_time_compare(&now, &zone->dumptime) >= 0 &&
		    DNS_ZONE_FLAG(zone, DNS_ZONEFLG_LOADED) &&
		    DNS_ZONE_FLAG(zone, DNS_ZONEFLG_NEEDDUMP)) {
			dumping = was_dumping(zone);
		} else
			dumping = true;
		UNLOCK_ZONE(zone);
		if (!dumping) {
			result = zone_dump(zone, true);
			if (result != ISC_R_SUCCESS)
				dns_zone_log(zone, ISC_LOG_WARNING,
					     "dump failed: %s",
					     dns_result_totext(result));
		}
		break;
	default:
		break;
	}


	switch (zone->type) {
	case dns_zone_master:
	case dns_zone_redirect:
		if ((DNS_ZONE_FLAG(zone, DNS_ZONEFLG_NEEDNOTIFY) ||
		     DNS_ZONE_FLAG(zone, DNS_ZONEFLG_NEEDSTARTUPNOTIFY))&&
		    isc_time_compare(&now, &zone->notifytime) >= 0)
			zone_notify(zone, &now);
	default:
		break;
	}


	switch (zone->type) {
	case dns_zone_key:
		if (isc_time_compare(&now, &zone->refreshkeytime) >= 0) {
			if (DNS_ZONE_FLAG(zone, DNS_ZONEFLG_LOADED) &&
			    !DNS_ZONE_FLAG(zone, DNS_ZONEFLG_REFRESHING)) {
				zone_refreshkeys(zone);
			}
		}
		break;
	case dns_zone_master:
		if (!isc_time_isepoch(&zone->refreshkeytime) &&
		    isc_time_compare(&now, &zone->refreshkeytime) >= 0 &&
		    zone->rss_event == NULL)
			zone_rekey(zone);
	default:
		break;
	}

	switch (zone->type) {
	case dns_zone_master:
	case dns_zone_redirect:
	case dns_zone_slave:


		if (zone->rss_event != NULL)
			break;
		if (!isc_time_isepoch(&zone->signingtime) &&
		    isc_time_compare(&now, &zone->signingtime) >= 0)
			zone_sign(zone);
		else if (!isc_time_isepoch(&zone->resigntime) &&
		    isc_time_compare(&now, &zone->resigntime) >= 0)
			zone_resigninc(zone);
		else if (!isc_time_isepoch(&zone->nsec3chaintime) &&
			isc_time_compare(&now, &zone->nsec3chaintime) >= 0)
			zone_nsec3chain(zone);


		if (!isc_time_isepoch(&zone->keywarntime) &&
		    isc_time_compare(&now, &zone->keywarntime) >= 0)
			set_key_expiry_warning(zone, zone->key_expiry,
					       isc_time_seconds(&now));
		break;

	default:
		break;
	}
	zone_settimer(zone, &now);
}
