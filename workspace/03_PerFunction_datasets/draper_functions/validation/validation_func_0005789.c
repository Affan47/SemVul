vfsc_delete(Vfs_handle *handle, char *key)
{
  int st;
  char *reply, *request;
  Handle *h;

  h = (Handle *) handle->h;

  if (key != NULL)
	request = ds_xprintf("delete %s", key);
  else
	request = "delete";

  st = invoke_cgi(handle, HTTP_POST_METHOD, request, NULL, NULL, &reply);
  if (st == -1)
	return(-1);

  if (strcaseeq(reply, "yes"))
	return(1);

  return(0);
}
