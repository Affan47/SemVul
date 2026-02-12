dns_zone_markdirty(dns_zone_t *zone) {
	uint32_t serial;
	isc_result_t result = ISC_R_SUCCESS;
	dns_zone_t *secure = NULL;


 again:
	LOCK_ZONE(zone);
	if (zone->type == dns_zone_master) {
		if (inline_raw(zone)) {
			unsigned int soacount;
			secure = zone->secure;
			INSIST(secure != zone);
			TRYLOCK_ZONE(result, secure);
			if (result != ISC_R_SUCCESS) {
				UNLOCK_ZONE(zone);
				secure = NULL;
				isc_thread_yield();
				goto again;
			}

			ZONEDB_LOCK(&zone->dblock, isc_rwlocktype_read);
			if (zone->db != NULL) {
				result = zone_get_from_db(zone, zone->db, NULL,
							  &soacount, &serial,
							  NULL, NULL, NULL,
							  NULL, NULL);
			} else
				result = DNS_R_NOTLOADED;
			ZONEDB_UNLOCK(&zone->dblock, isc_rwlocktype_read);
			if (result == ISC_R_SUCCESS && soacount > 0U)
				zone_send_secureserial(zone, serial);
		}


		if (result == ISC_R_SUCCESS)
			set_resigntime(zone);
	}
	if (secure != NULL)
		UNLOCK_ZONE(secure);
	zone_needdump(zone, DNS_DUMP_DELAY);
	UNLOCK_ZONE(zone);
}
