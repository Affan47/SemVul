baseURL(Buffer *buf)
{
    if (buf->bufferprop & BP_NO_URL) {

	return NULL;
    }
    if (buf->baseURL != NULL) {

	return buf->baseURL;
    }
    else if (IS_EMPTY_PARSED_URL(&buf->currentURL))
	return NULL;
    else
	return &buf->currentURL;
}
