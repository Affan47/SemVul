dns_zone_getrequeststats(dns_zone_t *zone) {


	if (zone->requeststats_on)
		return (zone->requeststats);
	else
		return (NULL);
}
