maybe_send_secure(dns_zone_t *zone) {
	isc_result_t result;


	if (zone->raw->db != NULL) {
		if (zone->db != NULL) {
			uint32_t serial;
			unsigned int soacount;

			result = zone_get_from_db(zone->raw, zone->raw->db,
						  NULL, &soacount, &serial,
						  NULL, NULL, NULL, NULL, NULL);
			if (result == ISC_R_SUCCESS && soacount > 0U)
				zone_send_secureserial(zone->raw, serial);
		} else
			zone_send_securedb(zone->raw, zone->raw->db);

	} else
		DNS_ZONE_SETFLAG(zone->raw, DNS_ZONEFLG_SENDSECURE);
}
