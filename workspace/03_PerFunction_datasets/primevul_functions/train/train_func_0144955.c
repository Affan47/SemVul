static CURLMcode multi_runsingle(struct Curl_multi *multi,
                                 struct timeval now,
                                 struct Curl_easy *data)
{
  struct Curl_message *msg = NULL;
  bool connected;
  bool async;
  bool protocol_connect = FALSE;
  bool dophase_done = FALSE;
  bool done = FALSE;
  CURLMcode rc;
  CURLcode result = CURLE_OK;
  struct SingleRequest *k;
  long timeout_ms;
  int control;

  if(!GOOD_EASY_HANDLE(data))
    return CURLM_BAD_EASY_HANDLE;

  do {
    bool disconnect_conn = FALSE;
    rc = CURLM_OK;


    if(data->state.pipe_broke) {
      infof(data, "Pipe broke: handle %p, url = %s\n",
            (void *)data, data->state.path);

      if(data->mstate < CURLM_STATE_COMPLETED) {

        multistate(data, CURLM_STATE_CONNECT);
        rc = CURLM_CALL_MULTI_PERFORM;
        result = CURLE_OK;
      }

      data->state.pipe_broke = FALSE;
      data->easy_conn = NULL;
      continue;
    }

    if(!data->easy_conn &&
       data->mstate > CURLM_STATE_CONNECT &&
       data->mstate < CURLM_STATE_DONE) {


      failf(data, "In state %d with no easy_conn, bail out!\n", data->mstate);
      return CURLM_INTERNAL_ERROR;
    }

    if(multi_ischanged(multi, TRUE)) {
      DEBUGF(infof(data, "multi changed, check CONNECT_PEND queue!\n"));
      Curl_multi_process_pending_handles(multi);
    }

    if(data->easy_conn && data->mstate > CURLM_STATE_CONNECT &&
       data->mstate < CURLM_STATE_COMPLETED)

      data->easy_conn->data = data;

    if(data->easy_conn &&
       (data->mstate >= CURLM_STATE_CONNECT) &&
       (data->mstate < CURLM_STATE_COMPLETED)) {


      timeout_ms = Curl_timeleft(data, &now,
                                 (data->mstate <= CURLM_STATE_WAITDO)?
                                 TRUE:FALSE);

      if(timeout_ms < 0) {

        if(data->mstate == CURLM_STATE_WAITRESOLVE)
          failf(data, "Resolving timed out after %ld milliseconds",
                Curl_tvdiff(now, data->progress.t_startsingle));
        else if(data->mstate == CURLM_STATE_WAITCONNECT)
          failf(data, "Connection timed out after %ld milliseconds",
                Curl_tvdiff(now, data->progress.t_startsingle));
        else {
          k = &data->req;
          if(k->size != -1) {
            failf(data, "Operation timed out after %ld milliseconds with %"
                  CURL_FORMAT_CURL_OFF_T " out of %"
                  CURL_FORMAT_CURL_OFF_T " bytes received",
                  Curl_tvdiff(now, data->progress.t_startsingle),
                  k->bytecount, k->size);
          }
          else {
            failf(data, "Operation timed out after %ld milliseconds with %"
                  CURL_FORMAT_CURL_OFF_T " bytes received",
                  Curl_tvdiff(now, data->progress.t_startsingle),
                  k->bytecount);
          }
        }


        if(data->mstate > CURLM_STATE_DO) {
          connclose(data->easy_conn, "Disconnected with pending data");
          disconnect_conn = TRUE;
        }
        result = CURLE_OPERATION_TIMEDOUT;
        (void)multi_done(&data->easy_conn, result, TRUE);

        goto statemachine_end;
      }
    }

    switch(data->mstate) {
    case CURLM_STATE_INIT:

      result=Curl_pretransfer(data);

      if(!result) {

        multistate(data, CURLM_STATE_CONNECT);
        Curl_pgrsTime(data, TIMER_STARTOP);
        rc = CURLM_CALL_MULTI_PERFORM;
      }
      break;

    case CURLM_STATE_CONNECT_PEND:


      break;

    case CURLM_STATE_CONNECT:

      Curl_pgrsTime(data, TIMER_STARTSINGLE);
      result = Curl_connect(data, &data->easy_conn,
                            &async, &protocol_connect);
      if(CURLE_NO_CONNECTION_AVAILABLE == result) {


        multistate(data, CURLM_STATE_CONNECT_PEND);


        if(!Curl_llist_insert_next(multi->pending, multi->pending->tail, data))
          result = CURLE_OUT_OF_MEMORY;
        else
          result = CURLE_OK;
        break;
      }

      if(!result) {

        result = Curl_add_handle_to_pipeline(data, data->easy_conn);
        if(result)
          disconnect_conn = TRUE;
        else {
          if(async)

            multistate(data, CURLM_STATE_WAITRESOLVE);
          else {


            rc = CURLM_CALL_MULTI_PERFORM;

            if(protocol_connect)
              multistate(data, Curl_pipeline_wanted(multi, CURLPIPE_HTTP1)?
                         CURLM_STATE_WAITDO:CURLM_STATE_DO);
            else {
#ifndef CURL_DISABLE_HTTP
              if(data->easy_conn->tunnel_state[FIRSTSOCKET] == TUNNEL_CONNECT)
                multistate(data, CURLM_STATE_WAITPROXYCONNECT);
              else
#endif
                multistate(data, CURLM_STATE_WAITCONNECT);
            }
          }
        }
      }
      break;

    case CURLM_STATE_WAITRESOLVE:

    {
      struct Curl_dns_entry *dns = NULL;
      struct connectdata *conn = data->easy_conn;
      const char *hostname;

      if(conn->bits.proxy)
        hostname = conn->proxy.name;
      else if(conn->bits.conn_to_host)
        hostname = conn->conn_to_host.name;
      else
        hostname = conn->host.name;


      dns = Curl_fetch_addr(conn, hostname, (int)conn->port);

      if(dns) {
#ifdef CURLRES_ASYNCH
        conn->async.dns = dns;
        conn->async.done = TRUE;
#endif
        result = CURLE_OK;
        infof(data, "Hostname '%s' was found in DNS cache\n", hostname);
      }

      if(!dns)
        result = Curl_resolver_is_resolved(data->easy_conn, &dns);


      singlesocket(multi, data);

      if(dns) {


        result = Curl_async_resolved(data->easy_conn, &protocol_connect);

        if(result)


          data->easy_conn = NULL;
        else {

          rc = CURLM_CALL_MULTI_PERFORM;
          if(protocol_connect)
            multistate(data, Curl_pipeline_wanted(multi, CURLPIPE_HTTP1)?
                       CURLM_STATE_WAITDO:CURLM_STATE_DO);
          else {
#ifndef CURL_DISABLE_HTTP
            if(data->easy_conn->tunnel_state[FIRSTSOCKET] == TUNNEL_CONNECT)
              multistate(data, CURLM_STATE_WAITPROXYCONNECT);
            else
#endif
              multistate(data, CURLM_STATE_WAITCONNECT);
          }
        }
      }

      if(result) {

        disconnect_conn = TRUE;
        break;
      }
    }
    break;

#ifndef CURL_DISABLE_HTTP
    case CURLM_STATE_WAITPROXYCONNECT:

      result = Curl_http_connect(data->easy_conn, &protocol_connect);

      if(data->easy_conn->bits.proxy_connect_closed) {
        rc = CURLM_CALL_MULTI_PERFORM;

        result = CURLE_OK;
        multi_done(&data->easy_conn, CURLE_OK, FALSE);
        multistate(data, CURLM_STATE_CONNECT);
      }
      else if(!result) {
        if(data->easy_conn->tunnel_state[FIRSTSOCKET] == TUNNEL_COMPLETE) {
          rc = CURLM_CALL_MULTI_PERFORM;

          multistate(data, CURLM_STATE_SENDPROTOCONNECT);
        }
      }
      break;
#endif

    case CURLM_STATE_WAITCONNECT:

      result = Curl_is_connected(data->easy_conn, FIRSTSOCKET, &connected);
      if(connected && !result) {
        rc = CURLM_CALL_MULTI_PERFORM;
        multistate(data, data->easy_conn->bits.tunnel_proxy?
                   CURLM_STATE_WAITPROXYCONNECT:
                   CURLM_STATE_SENDPROTOCONNECT);
      }
      else if(result) {


        disconnect_conn = TRUE;
        break;
      }
      break;

    case CURLM_STATE_SENDPROTOCONNECT:
      result = Curl_protocol_connect(data->easy_conn, &protocol_connect);
      if(!protocol_connect)

        multistate(data, CURLM_STATE_PROTOCONNECT);
      else if(!result) {

        multistate(data, Curl_pipeline_wanted(multi, CURLPIPE_HTTP1)?
                   CURLM_STATE_WAITDO:CURLM_STATE_DO);
        rc = CURLM_CALL_MULTI_PERFORM;
      }
      else if(result) {

        Curl_posttransfer(data);
        multi_done(&data->easy_conn, result, TRUE);
        disconnect_conn = TRUE;
      }
      break;

    case CURLM_STATE_PROTOCONNECT:

      result = Curl_protocol_connecting(data->easy_conn, &protocol_connect);
      if(!result && protocol_connect) {

        multistate(data, Curl_pipeline_wanted(multi, CURLPIPE_HTTP1)?
                   CURLM_STATE_WAITDO:CURLM_STATE_DO);
        rc = CURLM_CALL_MULTI_PERFORM;
      }
      else if(result) {

        Curl_posttransfer(data);
        multi_done(&data->easy_conn, result, TRUE);
        disconnect_conn = TRUE;
      }
      break;

    case CURLM_STATE_WAITDO:

      if(Curl_pipeline_checkget_write(data, data->easy_conn)) {

        multistate(data, CURLM_STATE_DO);
        rc = CURLM_CALL_MULTI_PERFORM;
      }
      break;

    case CURLM_STATE_DO:
      if(data->set.connect_only) {

        connkeep(data->easy_conn, "CONNECT_ONLY");
        multistate(data, CURLM_STATE_DONE);
        result = CURLE_OK;
        rc = CURLM_CALL_MULTI_PERFORM;
      }
      else {

        result = multi_do(&data->easy_conn, &dophase_done);


        if(!result) {
          if(!dophase_done) {

            if(data->set.wildcardmatch) {
              struct WildcardData *wc = &data->wildcard;
              if(wc->state == CURLWC_DONE || wc->state == CURLWC_SKIP) {

                multi_done(&data->easy_conn, CURLE_OK, FALSE);
                multistate(data, CURLM_STATE_DONE);
                rc = CURLM_CALL_MULTI_PERFORM;
                break;
              }
            }


            multistate(data, CURLM_STATE_DOING);
            rc = CURLM_OK;
          }


          else if(data->easy_conn->bits.do_more) {


            multistate(data, CURLM_STATE_DO_MORE);
            rc = CURLM_OK;
          }
          else {

            multistate(data, CURLM_STATE_DO_DONE);
            rc = CURLM_CALL_MULTI_PERFORM;
          }
        }
        else if((CURLE_SEND_ERROR == result) &&
                data->easy_conn->bits.reuse) {


          char *newurl = NULL;
          followtype follow=FOLLOW_NONE;
          CURLcode drc;
          bool retry = FALSE;

          drc = Curl_retry_request(data->easy_conn, &newurl);
          if(drc) {

            result = drc;
            disconnect_conn = TRUE;
          }
          else
            retry = (newurl)?TRUE:FALSE;

          Curl_posttransfer(data);
          drc = multi_done(&data->easy_conn, result, FALSE);


          if(retry) {
            if(!drc || (drc == CURLE_SEND_ERROR)) {
              follow = FOLLOW_RETRY;
              drc = Curl_follow(data, newurl, follow);
              if(!drc) {
                multistate(data, CURLM_STATE_CONNECT);
                rc = CURLM_CALL_MULTI_PERFORM;
                result = CURLE_OK;
              }
              else {

                result = drc;
                free(newurl);
              }
            }
            else {

              result = drc;
              free(newurl);
            }
          }
          else {

            disconnect_conn = TRUE;
            free(newurl);
          }
        }
        else {

          Curl_posttransfer(data);
          if(data->easy_conn)
            multi_done(&data->easy_conn, result, FALSE);
          disconnect_conn = TRUE;
        }
      }
      break;

    case CURLM_STATE_DOING:

      result = Curl_protocol_doing(data->easy_conn,
                                   &dophase_done);
      if(!result) {
        if(dophase_done) {

          multistate(data, data->easy_conn->bits.do_more?
                     CURLM_STATE_DO_MORE:
                     CURLM_STATE_DO_DONE);
          rc = CURLM_CALL_MULTI_PERFORM;
        }
      }
      else {

        Curl_posttransfer(data);
        multi_done(&data->easy_conn, result, FALSE);
        disconnect_conn = TRUE;
      }
      break;

    case CURLM_STATE_DO_MORE:


      result = multi_do_more(data->easy_conn, &control);


      if(!result) {
        if(control) {


          multistate(data, control==1?
                     CURLM_STATE_DO_DONE:
                     CURLM_STATE_DOING);
          rc = CURLM_CALL_MULTI_PERFORM;
        }
        else

          rc = CURLM_OK;
      }
      else {

        Curl_posttransfer(data);
        multi_done(&data->easy_conn, result, FALSE);
        disconnect_conn = TRUE;
      }
      break;

    case CURLM_STATE_DO_DONE:

      Curl_move_handle_from_send_to_recv_pipe(data, data->easy_conn);

      Curl_multi_process_pending_handles(multi);


      if((data->easy_conn->sockfd != CURL_SOCKET_BAD) ||
         (data->easy_conn->writesockfd != CURL_SOCKET_BAD))
        multistate(data, CURLM_STATE_WAITPERFORM);
      else
        multistate(data, CURLM_STATE_DONE);
      rc = CURLM_CALL_MULTI_PERFORM;
      break;

    case CURLM_STATE_WAITPERFORM:

      if(Curl_pipeline_checkget_read(data, data->easy_conn)) {

        multistate(data, CURLM_STATE_PERFORM);
        rc = CURLM_CALL_MULTI_PERFORM;
      }
      break;

    case CURLM_STATE_TOOFAST:

      if(Curl_pgrsUpdate(data->easy_conn))
        result = CURLE_ABORTED_BY_CALLBACK;
      else
        result = Curl_speedcheck(data, now);

      if(( (data->set.max_send_speed == 0) ||
           (data->progress.ulspeed < data->set.max_send_speed))  &&
         ( (data->set.max_recv_speed == 0) ||
           (data->progress.dlspeed < data->set.max_recv_speed)))
        multistate(data, CURLM_STATE_PERFORM);
      break;

    case CURLM_STATE_PERFORM:
    {
      char *newurl = NULL;
      bool retry = FALSE;


      if((data->set.max_send_speed > 0) &&
         (data->progress.ulspeed > data->set.max_send_speed)) {
        int buffersize;

        multistate(data, CURLM_STATE_TOOFAST);


        buffersize = (int)(data->set.buffer_size ?
                           data->set.buffer_size : BUFSIZE);
        timeout_ms = Curl_sleep_time(data->set.max_send_speed,
                                     data->progress.ulspeed, buffersize);
        Curl_expire_latest(data, timeout_ms);
        break;
      }


      if((data->set.max_recv_speed > 0) &&
         (data->progress.dlspeed > data->set.max_recv_speed)) {
        int buffersize;

        multistate(data, CURLM_STATE_TOOFAST);


        buffersize = (int)(data->set.buffer_size ?
                           data->set.buffer_size : BUFSIZE);
        timeout_ms = Curl_sleep_time(data->set.max_recv_speed,
                                     data->progress.dlspeed, buffersize);
        Curl_expire_latest(data, timeout_ms);
        break;
      }


      result = Curl_readwrite(data->easy_conn, data, &done);

      k = &data->req;

      if(!(k->keepon & KEEP_RECV))

        Curl_pipeline_leave_read(data->easy_conn);

      if(!(k->keepon & KEEP_SEND))

        Curl_pipeline_leave_write(data->easy_conn);

      if(done || (result == CURLE_RECV_ERROR)) {


        CURLcode ret = Curl_retry_request(data->easy_conn, &newurl);
        if(!ret)
          retry = (newurl)?TRUE:FALSE;

        if(retry) {


          result = CURLE_OK;
          done = TRUE;
        }
      }

      if(result) {


        if(!(data->easy_conn->handler->flags & PROTOPT_DUAL) &&
           result != CURLE_HTTP2_STREAM)
          connclose(data->easy_conn, "Transfer returned error");

        Curl_posttransfer(data);
        multi_done(&data->easy_conn, result, FALSE);
      }
      else if(done) {
        followtype follow=FOLLOW_NONE;


        Curl_posttransfer(data);


        Curl_removeHandleFromPipeline(data, data->easy_conn->recv_pipe);


        if(data->easy_conn->recv_pipe->head)
          Curl_expire_latest(data->easy_conn->recv_pipe->head->ptr, 1);


        Curl_multi_process_pending_handles(multi);


        if(data->req.newurl || retry) {
          if(!retry) {


            free(newurl);
            newurl = data->req.newurl;
            data->req.newurl = NULL;
            follow = FOLLOW_REDIR;
          }
          else
            follow = FOLLOW_RETRY;
          result = multi_done(&data->easy_conn, CURLE_OK, FALSE);
          if(!result) {
            result = Curl_follow(data, newurl, follow);
            if(!result) {
              multistate(data, CURLM_STATE_CONNECT);
              rc = CURLM_CALL_MULTI_PERFORM;
              newurl = NULL;


            }
          }
        }
        else {


          if(data->req.location) {
            free(newurl);
            newurl = data->req.location;
            data->req.location = NULL;
            result = Curl_follow(data, newurl, FOLLOW_FAKE);
            if(!result)
              newurl = NULL;
            else
              disconnect_conn = TRUE;
          }

          multistate(data, CURLM_STATE_DONE);
          rc = CURLM_CALL_MULTI_PERFORM;
        }
      }

      free(newurl);
      break;
    }

    case CURLM_STATE_DONE:

      rc = CURLM_CALL_MULTI_PERFORM;

      if(data->easy_conn) {
        CURLcode res;


        Curl_removeHandleFromPipeline(data, data->easy_conn->recv_pipe);

        Curl_multi_process_pending_handles(multi);


        res = multi_done(&data->easy_conn, result, FALSE);


        if(!result)
          result = res;


        if(data->easy_conn)
          data->easy_conn = NULL;
      }

      if(data->set.wildcardmatch) {
        if(data->wildcard.state != CURLWC_DONE) {


          multistate(data, CURLM_STATE_INIT);
          break;
        }
      }


      multistate(data, CURLM_STATE_COMPLETED);
      break;

    case CURLM_STATE_COMPLETED:


      data->easy_conn = NULL;

      Curl_expire(data, 0);
      break;

    case CURLM_STATE_MSGSENT:
      data->result = result;
      return CURLM_OK;

    default:
      return CURLM_INTERNAL_ERROR;
    }
    statemachine_end:

    if(data->mstate < CURLM_STATE_COMPLETED) {
      if(result) {


        data->state.pipe_broke = FALSE;


        Curl_multi_process_pending_handles(multi);

        if(data->easy_conn) {

          Curl_pipeline_leave_write(data->easy_conn);
          Curl_pipeline_leave_read(data->easy_conn);
          Curl_removeHandleFromPipeline(data, data->easy_conn->send_pipe);
          Curl_removeHandleFromPipeline(data, data->easy_conn->recv_pipe);

          if(disconnect_conn) {

            bool dead_connection = result == CURLE_OPERATION_TIMEDOUT;

            Curl_disconnect(data->easy_conn, dead_connection);


            data->easy_conn = NULL;
          }
        }
        else if(data->mstate == CURLM_STATE_CONNECT) {

          (void)Curl_posttransfer(data);
        }

        multistate(data, CURLM_STATE_COMPLETED);
      }

      else if(data->easy_conn && Curl_pgrsUpdate(data->easy_conn)) {


        result = CURLE_ABORTED_BY_CALLBACK;
        connclose(data->easy_conn, "Aborted by callback");


        multistate(data, (data->mstate < CURLM_STATE_DONE)?
                   CURLM_STATE_DONE: CURLM_STATE_COMPLETED);
        rc = CURLM_CALL_MULTI_PERFORM;
      }
    }

    if(CURLM_STATE_COMPLETED == data->mstate) {

      msg = &data->msg;

      msg->extmsg.msg = CURLMSG_DONE;
      msg->extmsg.easy_handle = data;
      msg->extmsg.data.result = result;

      rc = multi_addmsg(multi, msg);

      multistate(data, CURLM_STATE_MSGSENT);
    }
  } while((rc == CURLM_CALL_MULTI_PERFORM) || multi_ischanged(multi, FALSE));

  data->result = result;


  return rc;
}
