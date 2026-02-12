zmgr_resume_xfrs(dns_zonemgr_t *zmgr, bool multi) {
	dns_zone_t *zone;
	dns_zone_t *next;

	for (zone = ISC_LIST_HEAD(zmgr->waiting_for_xfrin);
	     zone != NULL;
	     zone = next)
	{
		isc_result_t result;
		next = ISC_LIST_NEXT(zone, statelink);
		result = zmgr_start_xfrin_ifquota(zmgr, zone);
		if (result == ISC_R_SUCCESS) {
			if (multi)
				continue;


			break;
		} else if (result == ISC_R_QUOTA) {


			continue;
		} else {
			dns_zone_log(zone, ISC_LOG_DEBUG(1),
				     "starting zone transfer: %s",
				     isc_result_totext(result));
			break;
		}
	}
}
