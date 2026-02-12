dns_zone_rpz_enable(dns_zone_t *zone, dns_rpz_zones_t *rpzs,
		    dns_rpz_num_t rpz_num)
{


	if (strcmp(zone->db_argv[0], "rbt") != 0 &&
	    strcmp(zone->db_argv[0], "rbt64") != 0)
		return (ISC_R_NOTIMPLEMENTED);
	if (zone->masterformat == dns_masterformat_map)
		return (ISC_R_NOTIMPLEMENTED);


	LOCK_ZONE(zone);
	if (zone->rpzs != NULL) {
		REQUIRE(zone->rpzs == rpzs && zone->rpz_num == rpz_num);
	} else {
		REQUIRE(zone->rpz_num == DNS_RPZ_INVALID_NUM);
		dns_rpz_attach_rpzs(rpzs, &zone->rpzs);
		zone->rpz_num = rpz_num;
	}
	rpzs->defined |= DNS_RPZ_ZBIT(rpz_num);
	UNLOCK_ZONE(zone);

	return (ISC_R_SUCCESS);
}
