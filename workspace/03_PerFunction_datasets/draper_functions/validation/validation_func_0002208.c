storeEntryValidLength(const StoreEntry * e)
{
    squid_off_t diff;
    squid_off_t clen;
    const HttpReply *reply;
    assert(e->mem_obj != NULL);
    reply = e->mem_obj->reply;
    debug(20, 3) ("storeEntryValidLength: Checking '%s'\n", storeKeyText(e->hash.key));
    debug(20, 5) ("storeEntryValidLength:     object_len = %" PRINTF_OFF_T "\n",
	objectLen(e));
    debug(20, 5) ("storeEntryValidLength:         hdr_sz = %d\n",
	reply->hdr_sz);
    clen = httpReplyBodySize(e->mem_obj->method, reply);
    debug(20, 5) ("storeEntryValidLength: content_length = %" PRINTF_OFF_T "\n",
	clen);
    if (clen < 0) {
	debug(20, 5) ("storeEntryValidLength: Unspecified content length: %s\n",
	    storeKeyText(e->hash.key));
	return 1;
    }
    diff = reply->hdr_sz + clen - objectLen(e);
    if (diff == 0)
	return 1;
    debug(20, 2) ("storeEntryValidLength: %" PRINTF_OFF_T " bytes too %s; '%s'\n",
	diff < 0 ? -diff : diff,
	diff < 0 ? "big" : "small",
	storeKeyText(e->hash.key));
    return 0;
}
