static CURLcode pre_transfer(struct GlobalConfig *global,
                             struct per_transfer *per)
{
  curl_off_t uploadfilesize = -1;
  struct_stat fileinfo;
  CURLcode result = CURLE_OK;

  if(per->uploadfile && !stdin_upload(per->uploadfile)) {


#ifdef __VMS

    per->infd = -1;
    if(stat(per->uploadfile, &fileinfo) == 0) {
      fileinfo.st_size = VmsSpecialSize(uploadfile, &fileinfo);
      switch(fileinfo.st_fab_rfm) {
      case FAB$C_VAR:
      case FAB$C_VFC:
      case FAB$C_STMCR:
        per->infd = open(per->uploadfile, O_RDONLY | O_BINARY);
        break;
      default:
        per->infd = open(per->uploadfile, O_RDONLY | O_BINARY,
                        "rfm=stmlf", "ctx=stm");
      }
    }
    if(per->infd == -1)
#else
      per->infd = open(per->uploadfile, O_RDONLY | O_BINARY);
    if((per->infd == -1) || fstat(per->infd, &fileinfo))
#endif
    {
      helpf(global->errors, "Can't open '%s'!\n", per->uploadfile);
      if(per->infd != -1) {
        close(per->infd);
        per->infd = STDIN_FILENO;
      }
      return CURLE_READ_ERROR;
    }
    per->infdopen = TRUE;


    if(S_ISREG(fileinfo.st_mode))
      uploadfilesize = fileinfo.st_size;

    if(uploadfilesize != -1) {
      struct OperationConfig *config = per->config;
#ifdef CURL_DISABLE_LIBCURL_OPTION
      (void)config;
#endif
      my_setopt(per->curl, CURLOPT_INFILESIZE_LARGE, uploadfilesize);
    }
    per->input.fd = per->infd;
  }
  return result;
}
