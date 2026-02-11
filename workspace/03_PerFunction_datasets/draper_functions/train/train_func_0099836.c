httpd_emu(void *arg)
{
    HTTPClient *client;
    Octstr *ip;
    Octstr *url;
    List *headers;
    Octstr *body;
    List *cgivars;
    struct httpd_emu_arg *p;
    EventQueue *eq;

    p = arg;
    eq = p->eq;
    eq_add_producer(eq);
    semaphore_up(p->sema);

    for (;;) {
	client = http_accept_request(p->port, &ip, &url, &headers, &body,
	    	    	    	     &cgivars);
	if (client == NULL)
	    break;

	eq_append(eq, eq_create_http_request(client,
	    	    	    	    http_cgi_variable(cgivars, "arg")));
    	octstr_destroy(ip);
    	octstr_destroy(url);
	http_destroy_headers(headers);
    	octstr_destroy(body);
    	http_destroy_cgiargs(cgivars);
    }
    eq_remove_producer(eq);
    gw_free(p);
}
