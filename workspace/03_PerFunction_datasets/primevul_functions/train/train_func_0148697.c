dns_zone_setsignatures(dns_zone_t *zone, uint32_t signatures) {
	REQUIRE(DNS_ZONE_VALID(zone));


	if (signatures > INT32_MAX)
		signatures = INT32_MAX;
	else if (signatures == 0)
		signatures = 1;
	zone->signatures = signatures;
}
