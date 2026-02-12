static CURLcode readwrite_data(struct Curl_easy *data,
                               struct connectdata *conn,
                               struct SingleRequest *k,
                               int *didwhat, bool *done,
                               bool *comeback)
{
  CURLcode result = CURLE_OK;
  ssize_t nread;
  size_t excess = 0;
  bool readmore = FALSE;
  int maxloops = 100;
  char *buf = data->state.buffer;
  DEBUGASSERT(buf);

  *done = FALSE;
  *comeback = FALSE;


  do {
    bool is_empty_data = FALSE;
    size_t buffersize = data->set.buffer_size;
    size_t bytestoread = buffersize;
#ifdef USE_NGHTTP2
    bool is_http2 = ((conn->handler->protocol & PROTO_FAMILY_HTTP) &&
                     (conn->httpversion == 20));
#endif

    if(
#ifdef USE_NGHTTP2


       !is_http2 &&
#endif
       k->size != -1 && !k->header) {

      curl_off_t totalleft = k->size - k->bytecount;
      if(totalleft < (curl_off_t)bytestoread)
        bytestoread = (size_t)totalleft;
    }

    if(bytestoread) {

      result = Curl_read(data, conn->sockfd, buf, bytestoread, &nread);


      if(CURLE_AGAIN == result)
        break;

      if(result>0)
        return result;
    }
    else {


      DEBUGF(infof(data, "readwrite_data: we're done!\n"));
      nread = 0;
    }

    if(!k->bytecount) {
      Curl_pgrsTime(data, TIMER_STARTTRANSFER);
      if(k->exp100 > EXP100_SEND_DATA)

        k->start100 = Curl_now();
    }

    *didwhat |= KEEP_RECV;

    is_empty_data = ((nread == 0) && (k->bodywrites == 0)) ? TRUE : FALSE;

    if(0 < nread || is_empty_data) {
      buf[nread] = 0;
    }
    else {


#ifdef USE_NGHTTP2
      if(is_http2 && !nread)
        DEBUGF(infof(data, "nread == 0, stream closed, bailing\n"));
      else
#endif
        DEBUGF(infof(data, "nread <= 0, server closed connection, bailing\n"));
      k->keepon &= ~KEEP_RECV;
      break;
    }


    k->str = buf;

    if(conn->handler->readwrite) {
      result = conn->handler->readwrite(data, conn, &nread, &readmore);
      if(result)
        return result;
      if(readmore)
        break;
    }

#ifndef CURL_DISABLE_HTTP


    if(k->header) {

      bool stop_reading = FALSE;
      result = Curl_http_readwrite_headers(data, conn, &nread, &stop_reading);
      if(result)
        return result;

      if(conn->handler->readwrite &&
         (k->maxdownload <= 0 && nread > 0)) {
        result = conn->handler->readwrite(data, conn, &nread, &readmore);
        if(result)
          return result;
        if(readmore)
          break;
      }

      if(stop_reading) {


        if(nread > 0) {
          infof(data,
                "Excess found:"
                " excess = %zd"
                " url = %s (zero-length body)\n",
                nread, data->state.up.path);
        }

        break;
      }
    }
#endif


    if(!k->header && (nread > 0 || is_empty_data)) {

      if(data->set.opt_no_body) {

        streamclose(conn, "ignoring body");
        *done = TRUE;
        return CURLE_WEIRD_SERVER_REPLY;
      }

#ifndef CURL_DISABLE_HTTP
      if(0 == k->bodywrites && !is_empty_data) {


        if(conn->handler->protocol&(PROTO_FAMILY_HTTP|CURLPROTO_RTSP)) {

          result = Curl_http_firstwrite(data, conn, done);
          if(result || *done)
            return result;
        }
      }
#endif

      k->bodywrites++;


      if(data->set.verbose) {
        if(k->badheader) {
          Curl_debug(data, CURLINFO_DATA_IN,
                     Curl_dyn_ptr(&data->state.headerb),
                     Curl_dyn_len(&data->state.headerb));
          if(k->badheader == HEADER_PARTHEADER)
            Curl_debug(data, CURLINFO_DATA_IN,
                       k->str, (size_t)nread);
        }
        else
          Curl_debug(data, CURLINFO_DATA_IN,
                     k->str, (size_t)nread);
      }

#ifndef CURL_DISABLE_HTTP
      if(k->chunk) {


        CURLcode extra;
        CHUNKcode res =
          Curl_httpchunk_read(data, k->str, nread, &nread, &extra);

        if(CHUNKE_OK < res) {
          if(CHUNKE_PASSTHRU_ERROR == res) {
            failf(data, "Failed reading the chunked-encoded stream");
            return extra;
          }
          failf(data, "%s in chunked-encoding", Curl_chunked_strerror(res));
          return CURLE_RECV_ERROR;
        }
        if(CHUNKE_STOP == res) {

          k->keepon &= ~KEEP_RECV;


          if(conn->chunk.datasize) {
            infof(data, "Leftovers after chunking: % "
                  CURL_FORMAT_CURL_OFF_T "u bytes\n",
                  conn->chunk.datasize);
          }
        }

      }
#endif


      if((k->badheader == HEADER_PARTHEADER) && !k->ignorebody) {
        size_t headlen = Curl_dyn_len(&data->state.headerb);
        DEBUGF(infof(data, "Increasing bytecount by %zu\n", headlen));
        k->bytecount += headlen;
      }

      if((-1 != k->maxdownload) &&
         (k->bytecount + nread >= k->maxdownload)) {

        excess = (size_t)(k->bytecount + nread - k->maxdownload);
        if(excess > 0 && !k->ignorebody) {
          infof(data,
                "Excess found in a read:"
                " excess = %zu"
                ", size = %" CURL_FORMAT_CURL_OFF_T
                ", maxdownload = %" CURL_FORMAT_CURL_OFF_T
                ", bytecount = %" CURL_FORMAT_CURL_OFF_T "\n",
                excess, k->size, k->maxdownload, k->bytecount);
          connclose(conn, "excess found in a read");
        }

        nread = (ssize_t) (k->maxdownload - k->bytecount);
        if(nread < 0)
          nread = 0;

        k->keepon &= ~KEEP_RECV;
      }

      k->bytecount += nread;

      Curl_pgrsSetDownloadCounter(data, k->bytecount);

      if(!k->chunk && (nread || k->badheader || is_empty_data)) {


        if(k->badheader && !k->ignorebody) {


          size_t headlen = Curl_dyn_len(&data->state.headerb);


          if(k->maxdownload == -1 || (curl_off_t)headlen <= k->maxdownload)
            result = Curl_client_write(data, CLIENTWRITE_BODY,
                                       Curl_dyn_ptr(&data->state.headerb),
                                       headlen);
          else
            result = Curl_client_write(data, CLIENTWRITE_BODY,
                                       Curl_dyn_ptr(&data->state.headerb),
                                       (size_t)k->maxdownload);

          if(result)
            return result;
        }
        if(k->badheader < HEADER_ALLBAD) {


          if(data->set.http_ce_skip || !k->writer_stack) {
            if(!k->ignorebody) {
#ifndef CURL_DISABLE_POP3
              if(conn->handler->protocol & PROTO_FAMILY_POP3)
                result = Curl_pop3_write(data, k->str, nread);
              else
#endif
                result = Curl_client_write(data, CLIENTWRITE_BODY, k->str,
                                           nread);
            }
          }
          else if(!k->ignorebody)
            result = Curl_unencode_write(data, k->writer_stack, k->str, nread);
        }
        k->badheader = HEADER_NORMAL;

        if(result)
          return result;
      }

    }

    if(conn->handler->readwrite && excess) {

      k->str += nread;

      if(&k->str[excess] > &buf[data->set.buffer_size]) {


        excess = &buf[data->set.buffer_size] - k->str;
      }
      nread = (ssize_t)excess;

      result = conn->handler->readwrite(data, conn, &nread, &readmore);
      if(result)
        return result;

      if(readmore)
        k->keepon |= KEEP_RECV;
      break;
    }

    if(is_empty_data) {


      k->keepon &= ~KEEP_RECV;
    }

    if(k->keepon & KEEP_RECV_PAUSE) {

      break;
    }

  } while(data_pending(data) && maxloops--);

  if(maxloops <= 0) {

    conn->cselect_bits = CURL_CSELECT_IN;
    *comeback = TRUE;
  }

  if(((k->keepon & (KEEP_RECV|KEEP_SEND)) == KEEP_SEND) &&
     conn->bits.close) {


    infof(data, "we are done reading and this is set to close, stop send\n");
    k->keepon &= ~KEEP_SEND;
  }

  return CURLE_OK;
}
