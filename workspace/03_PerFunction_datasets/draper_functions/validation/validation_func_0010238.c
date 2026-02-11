http_response_append(struct http_header_t *http_hdr,
			 char *response,int len)
{
    if(http_hdr == NULL || response == NULL || len < 0) return 0;


    http_hdr->buffer = (char *)xrealloc(http_hdr->buffer,
					http_hdr->buffer_len + len + 1);

    memcpy(http_hdr->buffer + http_hdr->buffer_len, response, len);
    http_hdr->buffer_len += len;
    http_hdr->buffer[http_hdr->buffer_len] = '\0';

    return http_hdr->buffer_len;
}
