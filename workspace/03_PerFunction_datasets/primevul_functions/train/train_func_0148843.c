dns_zone_detach(dns_zone_t **zonep) {
	REQUIRE(zonep != NULL && DNS_ZONE_VALID(*zonep));
	dns_zone_t *zone = *zonep;
	*zonep = NULL;

	bool free_now = false;
	dns_zone_t *raw = NULL;
	dns_zone_t *secure = NULL;
	if (isc_refcount_decrement(&zone->erefs) == 1) {
		isc_refcount_destroy(&zone->erefs);

		LOCK_ZONE(zone);
		INSIST(zone != zone->raw);


		if (zone->task != NULL) {


			isc_event_t *ev = &zone->ctlevent;
			isc_task_send(zone->task, &ev);
		} else {


			INSIST(zone->view == NULL);
			free_now = true;
			raw = zone->raw;
			zone->raw = NULL;
			secure = zone->secure;
			zone->secure = NULL;
		}
		UNLOCK_ZONE(zone);
	}
	if (free_now) {
		if (raw != NULL) {
			dns_zone_detach(&raw);
		}
		if (secure != NULL) {
			dns_zone_idetach(&secure);
		}
		zone_free(zone);
	}
}
