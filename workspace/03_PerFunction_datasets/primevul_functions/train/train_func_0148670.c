dns_zone_setrefreshkeyinterval(dns_zone_t *zone, uint32_t interval) {
	REQUIRE(DNS_ZONE_VALID(zone));
	if (interval == 0)
		return (ISC_R_RANGE);

	if (interval > (24 * 60))
		interval = (24 * 60);

	zone->refreshkeyinterval = interval * 60;
	return (ISC_R_SUCCESS);
}
