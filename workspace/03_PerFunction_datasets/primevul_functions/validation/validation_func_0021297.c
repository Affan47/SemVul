static CURLcode telnet_do(struct Curl_easy *data, bool *done)
{
  CURLcode result;
  struct connectdata *conn = data->conn;
  curl_socket_t sockfd = conn->sock[FIRSTSOCKET];
#ifdef USE_WINSOCK
  WSAEVENT event_handle;
  WSANETWORKEVENTS events;
  HANDLE stdin_handle;
  HANDLE objs[2];
  DWORD  obj_count;
  DWORD  wait_timeout;
  DWORD readfile_read;
  int err;
#else
  timediff_t interval_ms;
  struct pollfd pfd[2];
  int poll_cnt;
  curl_off_t total_dl = 0;
  curl_off_t total_ul = 0;
#endif
  ssize_t nread;
  struct curltime now;
  bool keepon = TRUE;
  char *buf = data->state.buffer;
  struct TELNET *tn;

  *done = TRUE;

  result = init_telnet(data);
  if(result)
    return result;

  tn = data->req.p.telnet;

  result = check_telnet_options(data);
  if(result)
    return result;

#ifdef USE_WINSOCK


  event_handle = WSACreateEvent();
  if(event_handle == WSA_INVALID_EVENT) {
    failf(data, "WSACreateEvent failed (%d)", SOCKERRNO);
    return CURLE_FAILED_INIT;
  }


  if(WSAEventSelect(sockfd, event_handle, FD_READ|FD_CLOSE) == SOCKET_ERROR) {
    WSACloseEvent(event_handle);
    return CURLE_OK;
  }


  stdin_handle = GetStdHandle(STD_INPUT_HANDLE);


  objs[0] = event_handle;
  objs[1] = stdin_handle;


  if(GetFileType(stdin_handle) == FILE_TYPE_PIPE ||
     data->set.is_fread_set) {

    obj_count = 1;

    wait_timeout = 100;
  }
  else {
    obj_count = 2;
    wait_timeout = 1000;
  }


  while(keepon) {
    const DWORD buf_size = (DWORD)data->set.buffer_size;
    DWORD waitret = WaitForMultipleObjects(obj_count, objs,
                                           FALSE, wait_timeout);
    switch(waitret) {

    case WAIT_TIMEOUT:
    {
      for(;;) {
        if(data->set.is_fread_set) {
          size_t n;

          n = data->state.fread_func(buf, 1, buf_size, data->state.in);
          if(n == CURL_READFUNC_ABORT) {
            keepon = FALSE;
            result = CURLE_READ_ERROR;
            break;
          }

          if(n == CURL_READFUNC_PAUSE)
            break;

          if(n == 0)
            break;


          readfile_read = (DWORD)n;
        }
        else {

          if(!PeekNamedPipe(stdin_handle, NULL, 0, NULL,
                            &readfile_read, NULL)) {
            keepon = FALSE;
            result = CURLE_READ_ERROR;
            break;
          }

          if(!readfile_read)
            break;

          if(!ReadFile(stdin_handle, buf, buf_size,
                       &readfile_read, NULL)) {
            keepon = FALSE;
            result = CURLE_READ_ERROR;
            break;
          }
        }

        result = send_telnet_data(data, buf, readfile_read);
        if(result) {
          keepon = FALSE;
          break;
        }
      }
    }
    break;

    case WAIT_OBJECT_0 + 1:
    {
      if(!ReadFile(stdin_handle, buf, buf_size,
                   &readfile_read, NULL)) {
        keepon = FALSE;
        result = CURLE_READ_ERROR;
        break;
      }

      result = send_telnet_data(data, buf, readfile_read);
      if(result) {
        keepon = FALSE;
        break;
      }
    }
    break;

    case WAIT_OBJECT_0:
    {
      events.lNetworkEvents = 0;
      if(WSAEnumNetworkEvents(sockfd, event_handle, &events) == SOCKET_ERROR) {
        err = SOCKERRNO;
        if(err != EINPROGRESS) {
          infof(data, "WSAEnumNetworkEvents failed (%d)", err);
          keepon = FALSE;
          result = CURLE_READ_ERROR;
        }
        break;
      }
      if(events.lNetworkEvents & FD_READ) {

        result = Curl_read(data, sockfd, buf, data->set.buffer_size, &nread);

        if(result == CURLE_AGAIN)
          break;

        else if(result) {
          keepon = FALSE;
          break;
        }


        else if(nread <= 0) {
          keepon = FALSE;
          break;
        }

        result = telrcv(data, (unsigned char *) buf, nread);
        if(result) {
          keepon = FALSE;
          break;
        }


        if(tn->please_negotiate && !tn->already_negotiated) {
          negotiate(data);
          tn->already_negotiated = 1;
        }
      }
      if(events.lNetworkEvents & FD_CLOSE) {
        keepon = FALSE;
      }
    }
    break;

    }

    if(data->set.timeout) {
      now = Curl_now();
      if(Curl_timediff(now, conn->created) >= data->set.timeout) {
        failf(data, "Time-out");
        result = CURLE_OPERATION_TIMEDOUT;
        keepon = FALSE;
      }
    }
  }


  if(!WSACloseEvent(event_handle)) {
    infof(data, "WSACloseEvent failed (%d)", SOCKERRNO);
  }
#else
  pfd[0].fd = sockfd;
  pfd[0].events = POLLIN;

  if(data->set.is_fread_set) {
    poll_cnt = 1;
    interval_ms = 100;
  }
  else {

    pfd[1].fd = fileno((FILE *)data->state.in);
    pfd[1].events = POLLIN;
    poll_cnt = 2;
    interval_ms = 1 * 1000;
  }

  while(keepon) {
    switch(Curl_poll(pfd, poll_cnt, interval_ms)) {
    case -1:
      keepon = FALSE;
      continue;
    case 0:
      pfd[0].revents = 0;
      pfd[1].revents = 0;

    default:
      if(pfd[0].revents & POLLIN) {

        result = Curl_read(data, sockfd, buf, data->set.buffer_size, &nread);

        if(result == CURLE_AGAIN)
          break;

        if(result) {
          keepon = FALSE;
          break;
        }


        else if(nread <= 0) {
          keepon = FALSE;
          break;
        }

        total_dl += nread;
        Curl_pgrsSetDownloadCounter(data, total_dl);
        result = telrcv(data, (unsigned char *)buf, nread);
        if(result) {
          keepon = FALSE;
          break;
        }


        if(tn->please_negotiate && !tn->already_negotiated) {
          negotiate(data);
          tn->already_negotiated = 1;
        }
      }

      nread = 0;
      if(poll_cnt == 2) {
        if(pfd[1].revents & POLLIN) {
          nread = read(pfd[1].fd, buf, data->set.buffer_size);
        }
      }
      else {

        nread = (int)data->state.fread_func(buf, 1, data->set.buffer_size,
                                            data->state.in);
        if(nread == CURL_READFUNC_ABORT) {
          keepon = FALSE;
          break;
        }
        if(nread == CURL_READFUNC_PAUSE)
          break;
      }

      if(nread > 0) {
        result = send_telnet_data(data, buf, nread);
        if(result) {
          keepon = FALSE;
          break;
        }
        total_ul += nread;
        Curl_pgrsSetUploadCounter(data, total_ul);
      }
      else if(nread < 0)
        keepon = FALSE;

      break;
    }

    if(data->set.timeout) {
      now = Curl_now();
      if(Curl_timediff(now, conn->created) >= data->set.timeout) {
        failf(data, "Time-out");
        result = CURLE_OPERATION_TIMEDOUT;
        keepon = FALSE;
      }
    }

    if(Curl_pgrsUpdate(data)) {
      result = CURLE_ABORTED_BY_CALLBACK;
      break;
    }
  }
#endif

  Curl_setup_transfer(data, -1, -1, FALSE, -1);

  return result;
}
