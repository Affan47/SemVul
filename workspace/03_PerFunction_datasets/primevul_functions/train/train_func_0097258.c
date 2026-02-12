CURLcode Curl_readrewind(struct Curl_easy *data)
{
  struct connectdata *conn = data->conn;
  curl_mimepart *mimepart = &data->set.mimepost;

  conn->bits.rewindaftersend = FALSE;


  data->req.keepon &= ~KEEP_SEND;


  if(conn->handler->protocol & PROTO_FAMILY_HTTP) {
    struct HTTP *http = data->req.p.http;

    if(http->sendit)
      mimepart = http->sendit;
  }
  if(data->set.postfields)
    ;
  else if(data->state.httpreq == HTTPREQ_POST_MIME ||
          data->state.httpreq == HTTPREQ_POST_FORM) {
    CURLcode result = Curl_mime_rewind(mimepart);
    if(result) {
      failf(data, "Cannot rewind mime/post data");
      return result;
    }
  }
  else {
    if(data->set.seek_func) {
      int err;

      Curl_set_in_callback(data, true);
      err = (data->set.seek_func)(data->set.seek_client, 0, SEEK_SET);
      Curl_set_in_callback(data, false);
      if(err) {
        failf(data, "seek callback returned error %d", (int)err);
        return CURLE_SEND_FAIL_REWIND;
      }
    }
    else if(data->set.ioctl_func) {
      curlioerr err;

      Curl_set_in_callback(data, true);
      err = (data->set.ioctl_func)(data, CURLIOCMD_RESTARTREAD,
                                   data->set.ioctl_client);
      Curl_set_in_callback(data, false);
      infof(data, "the ioctl callback returned %d", (int)err);

      if(err) {
        failf(data, "ioctl callback returned error %d", (int)err);
        return CURLE_SEND_FAIL_REWIND;
      }
    }
    else {


      if(data->state.fread_func == (curl_read_callback)fread) {
        if(-1 != fseek(data->state.in, 0, SEEK_SET))

          return CURLE_OK;
      }


      failf(data, "necessary data rewind wasn't possible");
      return CURLE_SEND_FAIL_REWIND;
    }
  }
  return CURLE_OK;
}
