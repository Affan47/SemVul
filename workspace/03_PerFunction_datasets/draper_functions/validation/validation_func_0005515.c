headers_acceptable(List *push_headers, Octstr **content_header)
{
    gw_assert(push_headers);
    *content_header = http_header_find_first(push_headers, "Content-Type");

    if (*content_header == NULL) {
        *content_header = octstr_format("%s", "no content type header found");
        goto error;
    }

    if (!type_is(*content_header, "multipart/related")) {
        goto error;
    }

    if (!type_is(*content_header, "application/xml")) {
        goto error;
    }

    return 1;

error:
    warning(0, "PPG: headers_acceptable: got unacceptable push headers");
    return 0;
}
