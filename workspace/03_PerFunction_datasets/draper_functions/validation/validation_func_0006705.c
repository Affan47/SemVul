mkheader(struct REQUEST *req, int status, time_t mtime)
{
    int    i;
    for (i = 0; http[i].status != 0; i++)
	if (http[i].status == status)
	    break;
    req->status = status;
    req->lres = sprintf(req->hres,
			RESPONSE_START,
			http[i].head,server_name,
			req->keep_alive ? "Keep-Alive" : "Close");
    req->lres += sprintf(req->hres+req->lres,
			 "Content-Type: %s\r\n"
			 "Content-Length: %d\r\n",
			 req->mime,
			 req->lbody);
    if (mtime != -1)
	req->lres += strftime(req->hres+req->lres,80,
			      "Last-Modified: " RFCTIME "\r\n",
			      gmtime(&mtime));
    req->lres += strftime(req->hres+req->lres,80,
			  "Date: " RFCTIME "\r\n\r\n",
			  gmtime(&now));
    req->state = STATE_WRITE_HEADER;
    if (debug)
	fprintf(stderr,"%03d: %d, connection=%s\n",
		req->fd, status, req->keep_alive ? "Keep-Alive" : "Close");
}
