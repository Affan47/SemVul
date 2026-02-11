update_remote(unsigned char *sha1, struct remote_lock *lock)
{
	struct active_request_slot *slot;
	struct slot_results results;
	char *if_header;
	struct buffer out_buffer = { STRBUF_INIT, 0 };
	struct curl_slist *dav_headers = NULL;

	if_header = xmalloc(strlen(lock->token) + 25);
	sprintf(if_header, "If: (<opaquelocktoken:%s>)", lock->token);
	dav_headers = curl_slist_append(dav_headers, if_header);

	strbuf_addf(&out_buffer.buf, "%s\n", sha1_to_hex(sha1));

	slot = get_active_slot();
	slot->results = &results;
	curl_easy_setopt(slot->curl, CURLOPT_INFILE, &out_buffer);
	curl_easy_setopt(slot->curl, CURLOPT_INFILESIZE, out_buffer.buf.len);
	curl_easy_setopt(slot->curl, CURLOPT_READFUNCTION, fread_buffer);
	curl_easy_setopt(slot->curl, CURLOPT_WRITEFUNCTION, fwrite_null);
	curl_easy_setopt(slot->curl, CURLOPT_CUSTOMREQUEST, DAV_PUT);
	curl_easy_setopt(slot->curl, CURLOPT_HTTPHEADER, dav_headers);
	curl_easy_setopt(slot->curl, CURLOPT_UPLOAD, 1);
	curl_easy_setopt(slot->curl, CURLOPT_PUT, 1);
	curl_easy_setopt(slot->curl, CURLOPT_URL, lock->url);

	if (start_active_slot(slot)) {
		run_active_slot(slot);
		strbuf_release(&out_buffer.buf);
		free(if_header);
		if (results.curl_result != CURLE_OK) {
			fprintf(stderr,
				"PUT error: curl result=%d, HTTP code=%ld\n",
				results.curl_result, results.http_code);

			return 0;
		}
	} else {
		strbuf_release(&out_buffer.buf);
		free(if_header);
		fprintf(stderr, "Unable to start PUT request\n");
		return 0;
	}

	return 1;
}
