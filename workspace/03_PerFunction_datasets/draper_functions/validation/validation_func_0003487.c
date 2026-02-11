ne_request_destroy(ne_request *req)
{
    struct body_reader *rdr, *next_rdr;
    struct hook *hk, *next_hk;

    ne_free(req->uri);
    ne_free(req->method);

    for (rdr = req->body_readers; rdr != NULL; rdr = next_rdr) {
	next_rdr = rdr->next;
	ne_free(rdr);
    }

    free_response_headers(req);

    ne_buffer_destroy(req->headers);

    NE_DEBUG(NE_DBG_HTTP, "Running destroy hooks.\n");
    for (hk = req->session->destroy_req_hooks; hk; hk = hk->next) {
	ne_destroy_req_fn fn = (ne_destroy_req_fn)hk->fn;
	fn(req, hk->userdata);
    }

    for (hk = req->private; hk; hk = next_hk) {
	next_hk = hk->next;
	ne_free(hk);
    }
    for (hk = req->pre_send_hooks; hk; hk = next_hk) {
	next_hk = hk->next;
	ne_free(hk);
    }

    if (req->status.reason_phrase)
	ne_free(req->status.reason_phrase);

    NE_DEBUG(NE_DBG_HTTP, "Request ends.\n");
    ne_free(req);
}
