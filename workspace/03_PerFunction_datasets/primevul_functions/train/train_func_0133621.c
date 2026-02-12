static CURLcode file_upload(struct connectdata *conn)
{
  struct FILEPROTO *file = conn->data->req.protop;
  const char *dir = strchr(file->path, DIRSEP);
  int fd;
  int mode;
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  char *buf = data->state.buffer;
  curl_off_t bytecount = 0;
  struct_stat file_stat;
  const char *buf2;


  conn->data->req.upload_fromhere = buf;

  if(!dir)
    return CURLE_FILE_COULDNT_READ_FILE;

  if(!dir[1])
    return CURLE_FILE_COULDNT_READ_FILE;

#ifdef O_BINARY
#define MODE_DEFAULT O_WRONLY|O_CREAT|O_BINARY
#else
#define MODE_DEFAULT O_WRONLY|O_CREAT
#endif

  if(data->state.resume_from)
    mode = MODE_DEFAULT|O_APPEND;
  else
    mode = MODE_DEFAULT|O_TRUNC;

  fd = open(file->path, mode, conn->data->set.new_file_perms);
  if(fd < 0) {
    failf(data, "Can't open %s for writing", file->path);
    return CURLE_WRITE_ERROR;
  }

  if(-1 != data->state.infilesize)

    Curl_pgrsSetUploadSize(data, data->state.infilesize);


  if(data->state.resume_from < 0) {
    if(fstat(fd, &file_stat)) {
      close(fd);
      failf(data, "Can't get the size of %s", file->path);
      return CURLE_WRITE_ERROR;
    }
    data->state.resume_from = (curl_off_t)file_stat.st_size;
  }

  while(!result) {
    size_t nread;
    size_t nwrite;
    size_t readcount;
    result = Curl_fillreadbuffer(conn, data->set.buffer_size, &readcount);
    if(result)
      break;

    if(!readcount)
      break;

    nread = readcount;


    if(data->state.resume_from) {
      if((curl_off_t)nread <= data->state.resume_from) {
        data->state.resume_from -= nread;
        nread = 0;
        buf2 = buf;
      }
      else {
        buf2 = buf + data->state.resume_from;
        nread -= (size_t)data->state.resume_from;
        data->state.resume_from = 0;
      }
    }
    else
      buf2 = buf;


    nwrite = write(fd, buf2, nread);
    if(nwrite != nread) {
      result = CURLE_SEND_ERROR;
      break;
    }

    bytecount += nread;

    Curl_pgrsSetUploadCounter(data, bytecount);

    if(Curl_pgrsUpdate(conn))
      result = CURLE_ABORTED_BY_CALLBACK;
    else
      result = Curl_speedcheck(data, Curl_now());
  }
  if(!result && Curl_pgrsUpdate(conn))
    result = CURLE_ABORTED_BY_CALLBACK;

  close(fd);

  return result;
}
