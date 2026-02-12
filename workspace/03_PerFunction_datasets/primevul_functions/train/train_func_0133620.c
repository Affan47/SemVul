static CURLcode file_do(struct connectdata *conn, bool *done)
{


  CURLcode result = CURLE_OK;
  struct_stat statbuf;


  curl_off_t expected_size = 0;
  bool size_known;
  bool fstated = FALSE;
  struct Curl_easy *data = conn->data;
  char *buf = data->state.buffer;
  curl_off_t bytecount = 0;
  int fd;
  struct FILEPROTO *file;

  *done = TRUE;

  Curl_pgrsStartNow(data);

  if(data->set.upload)
    return file_upload(conn);

  file = conn->data->req.protop;


  fd = file->fd;


  if(-1 != fstat(fd, &statbuf)) {

    expected_size = statbuf.st_size;

    data->info.filetime = statbuf.st_mtime;
    fstated = TRUE;
  }

  if(fstated && !data->state.range && data->set.timecondition) {
    if(!Curl_meets_timecondition(data, data->info.filetime)) {
      *done = TRUE;
      return CURLE_OK;
    }
  }

  if(fstated) {
    time_t filetime;
    struct tm buffer;
    const struct tm *tm = &buffer;
    char header[80];
    msnprintf(header, sizeof(header),
              "Content-Length: %" CURL_FORMAT_CURL_OFF_T "\r\n",
              expected_size);
    result = Curl_client_write(conn, CLIENTWRITE_HEADER, header, 0);
    if(result)
      return result;

    result = Curl_client_write(conn, CLIENTWRITE_HEADER,
                               (char *)"Accept-ranges: bytes\r\n", 0);
    if(result)
      return result;

    filetime = (time_t)statbuf.st_mtime;
    result = Curl_gmtime(filetime, &buffer);
    if(result)
      return result;


    msnprintf(header, sizeof(header),
              "Last-Modified: %s, %02d %s %4d %02d:%02d:%02d GMT\r\n%s",
              Curl_wkday[tm->tm_wday?tm->tm_wday-1:6],
              tm->tm_mday,
              Curl_month[tm->tm_mon],
              tm->tm_year + 1900,
              tm->tm_hour,
              tm->tm_min,
              tm->tm_sec,
              data->set.opt_no_body ? "": "\r\n");
    result = Curl_client_write(conn, CLIENTWRITE_HEADER, header, 0);
    if(result)
      return result;

    Curl_pgrsSetDownloadSize(data, expected_size);
    if(data->set.opt_no_body)
      return result;
  }


  result = Curl_range(conn);
  if(result)
    return result;


  if(data->state.resume_from < 0) {
    if(!fstated) {
      failf(data, "Can't get the size of file.");
      return CURLE_READ_ERROR;
    }
    data->state.resume_from += (curl_off_t)statbuf.st_size;
  }

  if(data->state.resume_from <= expected_size)
    expected_size -= data->state.resume_from;
  else {
    failf(data, "failed to resume file:// transfer");
    return CURLE_BAD_DOWNLOAD_RESUME;
  }


  if(data->req.maxdownload > 0)
    expected_size = data->req.maxdownload;

  if(!fstated || (expected_size == 0))
    size_known = FALSE;
  else
    size_known = TRUE;


  if(fstated)
    Curl_pgrsSetDownloadSize(data, expected_size);

  if(data->state.resume_from) {
    if(data->state.resume_from !=
       lseek(fd, data->state.resume_from, SEEK_SET))
      return CURLE_BAD_DOWNLOAD_RESUME;
  }

  Curl_pgrsTime(data, TIMER_STARTTRANSFER);

  while(!result) {
    ssize_t nread;

    size_t bytestoread;

    if(size_known) {
      bytestoread = (expected_size < data->set.buffer_size) ?
        curlx_sotouz(expected_size) : (size_t)data->set.buffer_size;
    }
    else
      bytestoread = data->set.buffer_size-1;

    nread = read(fd, buf, bytestoread);

    if(nread > 0)
      buf[nread] = 0;

    if(nread <= 0 || (size_known && (expected_size == 0)))
      break;

    bytecount += nread;
    if(size_known)
      expected_size -= nread;

    result = Curl_client_write(conn, CLIENTWRITE_BODY, buf, nread);
    if(result)
      return result;

    Curl_pgrsSetDownloadCounter(data, bytecount);

    if(Curl_pgrsUpdate(conn))
      result = CURLE_ABORTED_BY_CALLBACK;
    else
      result = Curl_speedcheck(data, Curl_now());
  }
  if(Curl_pgrsUpdate(conn))
    result = CURLE_ABORTED_BY_CALLBACK;

  return result;
}
