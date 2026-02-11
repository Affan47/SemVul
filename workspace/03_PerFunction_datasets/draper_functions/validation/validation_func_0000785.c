free_http_header_access(header_mangler header[])
{
    int i;
    header_mangler **hdrp;
    for (i = 0; i < HDR_ENUM_END; i++) {
	free_acl_access(&header[i].access_list);
    }
    hdrp = &header[HDR_OTHER].next;
    while (*hdrp) {
	header_mangler *hdr = *hdrp;
	free_acl_access(&hdr->access_list);
	if (!hdr->replacement) {
	    *hdrp = hdr->next;
	    safe_free(hdr->name);
	    safe_free(hdr);
	} else {
	    hdrp = &hdr->next;
	}
    }
}
