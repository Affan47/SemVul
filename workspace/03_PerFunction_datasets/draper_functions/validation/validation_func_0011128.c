http_get_response_body(Http *h, char **reply, int *reply_len)
{
  int rc;
  Ds response;

  ds_init(&response);
  if (*reply_len > 0)
	response.len_limit = *reply_len;

  while ((rc = http_read_response_body(h, &response)) > 0)
	;

  if (rc == -1) {
	*reply = "Error reading HTTP response";
	return(-1);
  }

  if (ds_len(&response) == 0) {
	*reply = "";
	*reply_len = 0;
  }
  else {
	*reply_len = ds_len(&response);
	ds_appendc(&response, (int) '\0');
	*reply = ds_buf(&response);
  }

  return(0);
}
