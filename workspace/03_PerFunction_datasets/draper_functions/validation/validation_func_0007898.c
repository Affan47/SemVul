ns_server_sync(ns_server_t *server, char *args, isc_buffer_t *text) {
	isc_result_t result, tresult;
	dns_view_t *view;
	dns_zone_t *zone = NULL;
	char classstr[DNS_RDATACLASS_FORMATSIZE];
	char zonename[DNS_NAME_FORMATSIZE];
	const char *vname, *sep, *msg = NULL, *arg;
	isc_boolean_t cleanup = ISC_FALSE;

	(void) next_token(&args, " \t");

	arg = next_token(&args, " \t");
	if (arg != NULL &&
	    (strcmp(arg, "-clean") == 0 || strcmp(arg, "-clear") == 0)) {
		cleanup = ISC_TRUE;
		arg = next_token(&args, " \t");
	}

	result = zone_from_args(server, args, arg, &zone, NULL,
				text, ISC_FALSE);
	if (result != ISC_R_SUCCESS)
		return (result);

	if (zone == NULL) {
		result = isc_task_beginexclusive(server->task);
		RUNTIME_CHECK(result == ISC_R_SUCCESS);
		tresult = ISC_R_SUCCESS;
		for (view = ISC_LIST_HEAD(server->viewlist);
		     view != NULL;
		     view = ISC_LIST_NEXT(view, link)) {
			result = dns_zt_apply(view->zonetable, ISC_FALSE,
					      synczone, &cleanup);
			if (result != ISC_R_SUCCESS &&
			    tresult == ISC_R_SUCCESS)
				tresult = result;
		}
		isc_task_endexclusive(server->task);
		isc_log_write(ns_g_lctx, NS_LOGCATEGORY_GENERAL,
			      NS_LOGMODULE_SERVER, ISC_LOG_INFO,
			      "dumping all zones%s: %s",
			      cleanup ? ", removing journal files" : "",
			      isc_result_totext(result));
		return (tresult);
	}

	result = isc_task_beginexclusive(server->task);
	RUNTIME_CHECK(result == ISC_R_SUCCESS);
	result = synczone(zone, &cleanup);
	isc_task_endexclusive(server->task);

	if (msg != NULL && strlen(msg) < isc_buffer_availablelength(text))
		isc_buffer_putmem(text, (const unsigned char *)msg,
				  strlen(msg) + 1);

	view = dns_zone_getview(zone);
	if (strcmp(view->name, "_default") == 0 ||
	    strcmp(view->name, "_bind") == 0)
	{
		vname = "";
		sep = "";
	} else {
		vname = view->name;
		sep = " ";
	}
	dns_rdataclass_format(dns_zone_getclass(zone), classstr,
			      sizeof(classstr));
	dns_name_format(dns_zone_getorigin(zone),
			zonename, sizeof(zonename));
	isc_log_write(ns_g_lctx, NS_LOGCATEGORY_GENERAL,
		      NS_LOGMODULE_SERVER, ISC_LOG_INFO,
		      "sync: dumping zone '%s/%s'%s%s%s: %s",
		      zonename, classstr, sep, vname,
		      cleanup ? ", removing journal file" : "",
		      isc_result_totext(result));
	dns_zone_detach(&zone);
	return (result);
}
