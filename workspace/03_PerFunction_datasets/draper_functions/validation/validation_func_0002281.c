httpHeaderHasConnDir(const HttpHeader * hdr, const char *directive)
{
    String list;
    http_hdr_type ht;
    int res;

    if (httpHeaderHas(hdr, HDR_PROXY_CONNECTION))
	ht = HDR_PROXY_CONNECTION;
    else if (httpHeaderHas(hdr, HDR_CONNECTION))
	ht = HDR_CONNECTION;
    else
	return 0;

    list = httpHeaderGetList(hdr, ht);
    res = strListIsMember(&list, directive, ',');
    stringClean(&list);
    return res;
}
