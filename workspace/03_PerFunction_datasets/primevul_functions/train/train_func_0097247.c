static CURLcode readwrite_upload(struct Curl_easy *data,
                                 struct connectdata *conn,
                                 int *didwhat)
{
  ssize_t i, si;
  ssize_t bytes_written;
  CURLcode result;
  ssize_t nread;
  bool sending_http_headers = FALSE;
  struct SingleRequest *k = &data->req;

  if((k->bytecount == 0) && (k->writebytecount == 0))
    Curl_pgrsTime(data, TIMER_STARTTRANSFER);

  *didwhat |= KEEP_SEND;

  do {
    curl_off_t nbody;


    if(0 == k->upload_present) {
      result = Curl_get_upload_buffer(data);
      if(result)
        return result;

      k->upload_fromhere = data->state.ulbuf;

      if(!k->upload_done) {


        size_t fillcount;
        struct HTTP *http = k->p.http;

        if((k->exp100 == EXP100_SENDING_REQUEST) &&
           (http->sending == HTTPSEND_BODY)) {


          k->exp100 = EXP100_AWAITING_CONTINUE;
          k->keepon &= ~KEEP_SEND;
          k->start100 = Curl_now();
          *didwhat &= ~KEEP_SEND;

          Curl_expire(data, data->set.expect_100_timeout, EXPIRE_100_TIMEOUT);
          break;
        }

        if(conn->handler->protocol&(PROTO_FAMILY_HTTP|CURLPROTO_RTSP)) {
          if(http->sending == HTTPSEND_REQUEST)


            sending_http_headers = TRUE;
          else
            sending_http_headers = FALSE;
        }

        result = Curl_fillreadbuffer(data, data->set.upload_buffer_size,
                                     &fillcount);
        if(result)
          return result;

        nread = fillcount;
      }
      else
        nread = 0;

      if(!nread && (k->keepon & KEEP_SEND_PAUSE)) {

        break;
      }
      if(nread <= 0) {
        result = Curl_done_sending(data, k);
        if(result)
          return result;
        break;
      }


      k->upload_present = nread;


      if((!sending_http_headers) && (
#ifdef CURL_DO_LINEEND_CONV

         (data->state.prefer_ascii) ||
#endif
         (data->set.crlf))) {

        if(!data->state.scratch) {
          data->state.scratch = malloc(2 * data->set.upload_buffer_size);
          if(!data->state.scratch) {
            failf(data, "Failed to alloc scratch buffer");

            return CURLE_OUT_OF_MEMORY;
          }
        }


        for(i = 0, si = 0; i < nread; i++, si++) {
          if(k->upload_fromhere[i] == 0x0a) {
            data->state.scratch[si++] = 0x0d;
            data->state.scratch[si] = 0x0a;
            if(!data->set.crlf) {


              if(data->state.infilesize != -1)
                data->state.infilesize++;
            }
          }
          else
            data->state.scratch[si] = k->upload_fromhere[i];
        }

        if(si != nread) {


          nread = si;


          k->upload_fromhere = data->state.scratch;


          k->upload_present = nread;
        }
      }

#ifndef CURL_DISABLE_SMTP
      if(conn->handler->protocol & PROTO_FAMILY_SMTP) {
        result = Curl_smtp_escape_eob(data, nread);
        if(result)
          return result;
      }
#endif
    }
    else {


    }


    result = Curl_write(data,
                        conn->writesockfd,
                        k->upload_fromhere,
                        k->upload_present,
                        &bytes_written);
    if(result)
      return result;

    win_update_buffer_size(conn->writesockfd);

    if(k->pendingheader) {

      curl_off_t n = CURLMIN(k->pendingheader, bytes_written);

      Curl_debug(data, CURLINFO_HEADER_OUT, k->upload_fromhere, (size_t)n);
      k->pendingheader -= n;
      nbody = bytes_written - n;
    }
    else
      nbody = bytes_written;

    if(nbody) {

      Curl_debug(data, CURLINFO_DATA_OUT,
                 &k->upload_fromhere[bytes_written - nbody],
                 (size_t)nbody);

      k->writebytecount += nbody;
      Curl_pgrsSetUploadCounter(data, k->writebytecount);
    }

    if((!k->upload_chunky || k->forbidchunk) &&
       (k->writebytecount == data->state.infilesize)) {

      k->upload_done = TRUE;
      infof(data, "We are completely uploaded and fine");
    }

    if(k->upload_present != bytes_written) {


      k->upload_present -= bytes_written;


      k->upload_fromhere += bytes_written;
    }
    else {

      result = Curl_get_upload_buffer(data);
      if(result)
        return result;
      k->upload_fromhere = data->state.ulbuf;
      k->upload_present = 0;

      if(k->upload_done) {
        result = Curl_done_sending(data, k);
        if(result)
          return result;
      }
    }


  } while(0);

  return CURLE_OK;
}
