static void ev_request_free(REQUEST **prequest)
{
	REQUEST *request;

	if (!prequest || !*prequest) return;

	request = *prequest;

#ifdef WITH_COA
	if (request->coa) {


		request->coa->parent = NULL;
		ev_request_free(&request->coa);
	}


	if (request->parent && (request->parent->coa == request)) {
		request->parent->coa = NULL;
	}
#endif

	if (request->ev) fr_event_delete(el, &request->ev);
#ifdef WITH_PROXY
	if (request->in_proxy_hash) remove_from_proxy_hash(request);
#endif
	if (request->in_request_hash) remove_from_request_hash(request);

	request_free(prequest);
}
