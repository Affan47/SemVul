_handle_info_getnodeattr(int fd, int lrank, client_req_t *req)
{
	int rc = 0;
	client_resp_t *resp;
	char *key, *val;
	bool wait = false;

	debug3("mpi/pmi2: in _handle_info_getnodeattr from lrank %d", lrank);

	client_req_parse_body(req);
	client_req_get_str(req, KEY_KEY, &key);
	client_req_get_bool(req, WAIT_KEY, &wait);

	val = node_attr_get(key);

	if (val != NULL || (! wait)) {
		resp = client_resp_new();
		client_resp_append(resp, CMD_KEY"="GETNODEATTRRESP_CMD";"
				RC_KEY"=0;" );
		if (val == NULL) {
			client_resp_append(resp, FOUND_KEY"="FALSE_VAL";" );
		} else  {
			client_resp_append(resp, FOUND_KEY"="TRUE_VAL";"
					   VALUE_KEY"=%s;", val);
		}
		rc = client_resp_send(resp, fd);
		client_resp_free(resp);
	} else {
		rc = enqueue_nag_req(fd, lrank, key);
	}

	debug3("mpi/pmi2: out _handle_info_getnodeattr");
	return rc;
}
