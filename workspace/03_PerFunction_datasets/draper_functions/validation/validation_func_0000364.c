mailimap_cont_req_or_resp_data_parse(mailstream * fd, MMAPString * buffer,
				     size_t * indx,
				     struct mailimap_cont_req_or_resp_data **
				     result,
				     size_t progr_rate,
				     progress_function * progr_fun)
{
  size_t cur_token;
  struct mailimap_cont_req_or_resp_data * cont_req_or_resp_data;
  struct mailimap_continue_req * cont_req;
  struct mailimap_response_data * resp_data;
  int type;
  int r;
  int res;

  cur_token = * indx;

  cont_req = NULL;
  resp_data = NULL;
  type = MAILIMAP_RESP_ERROR;

  r = mailimap_continue_req_parse(fd, buffer, &cur_token, &cont_req,
				  progr_rate, progr_fun);
  if (r == MAILIMAP_NO_ERROR)
    type = MAILIMAP_RESP_CONT_REQ;

  if (r == MAILIMAP_ERROR_PARSE) {
    r = mailimap_response_data_parse(fd, buffer, &cur_token, &resp_data,
				     progr_rate, progr_fun);
    if (r == MAILIMAP_NO_ERROR)
      type = MAILIMAP_RESP_RESP_DATA;
  }

  if (r != MAILIMAP_NO_ERROR) {
    res = r;
    goto err;
  }


  if (!mailstream_read_line_append(fd, buffer)) {
    res = MAILIMAP_ERROR_STREAM;
    goto free;
  }

  cont_req_or_resp_data =
    mailimap_cont_req_or_resp_data_new(type, cont_req, resp_data);
  if (cont_req_or_resp_data == NULL) {
    res = MAILIMAP_ERROR_MEMORY;
    goto free;
  }

  * result = cont_req_or_resp_data;
  * indx = cur_token;

  return MAILIMAP_NO_ERROR;

 free:
  if (cont_req != NULL)
    mailimap_continue_req_free(cont_req);
  if (resp_data != NULL)
    mailimap_response_data_free(resp_data);
 err:
  return res;
}
