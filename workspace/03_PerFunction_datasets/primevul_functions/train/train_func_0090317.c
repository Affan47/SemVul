static CURLcode post_per_transfer(struct GlobalConfig *global,
                                  struct per_transfer *per,
                                  CURLcode result,
                                  bool *retryp,
                                  long *delay)
{
  struct OutStruct *outs = &per->outs;
  CURL *curl = per->curl;
  struct OperationConfig *config = per->config;

  if(!curl || !config)
    return result;

  *retryp = FALSE;
  *delay = 0;

  if(per->infdopen)
    close(per->infd);

#ifdef __VMS
  if(is_vms_shell()) {

    if(!global->showerror)
      vms_show = VMSSTS_HIDE;
  }
  else
#endif
    if(!config->synthetic_error && result && global->showerror) {
      fprintf(global->errors, "curl: (%d) %s\n", result,
              (per->errorbuffer[0]) ? per->errorbuffer :
              curl_easy_strerror(result));
      if(result == CURLE_PEER_FAILED_VERIFICATION)
        fputs(CURL_CA_CERT_ERRORMSG, global->errors);
    }
    else if(config->failwithbody) {

      long code = 0;
      curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);
      if(code >= 400) {
        if(global->showerror)
          fprintf(global->errors,
                  "curl: (%d) The requested URL returned error: %ld\n",
                  CURLE_HTTP_RETURNED_ERROR, code);
        result = CURLE_HTTP_RETURNED_ERROR;
      }
    }

  if(!result && config->xattr && outs->fopened && outs->stream) {
    int rc = fwrite_xattr(curl, fileno(outs->stream));
    if(rc)
      warnf(config->global, "Error setting extended attributes on '%s': %s\n",
            outs->filename, strerror(errno));
  }

  if(!result && !outs->stream && !outs->bytes) {


    long cond_unmet = 0L;


    curl_easy_getinfo(curl, CURLINFO_CONDITION_UNMET, &cond_unmet);
    if(!cond_unmet && !tool_create_output_file(outs, config))
      result = CURLE_WRITE_ERROR;
  }

  if(!outs->s_isreg && outs->stream) {

    int rc = fflush(outs->stream);
    if(!result && rc) {

      result = CURLE_WRITE_ERROR;
      if(global->showerror)
        fprintf(global->errors, "curl: (%d) Failed writing body\n", result);
    }
  }


  if(per->retry_numretries &&
     (!config->retry_maxtime ||
      (tvdiff(tvnow(), per->retrystart) <
       config->retry_maxtime*1000L)) ) {
    enum {
      RETRY_NO,
      RETRY_ALL_ERRORS,
      RETRY_TIMEOUT,
      RETRY_CONNREFUSED,
      RETRY_HTTP,
      RETRY_FTP,
      RETRY_LAST
    } retry = RETRY_NO;
    long response = 0;
    if((CURLE_OPERATION_TIMEDOUT == result) ||
       (CURLE_COULDNT_RESOLVE_HOST == result) ||
       (CURLE_COULDNT_RESOLVE_PROXY == result) ||
       (CURLE_FTP_ACCEPT_TIMEOUT == result))

      retry = RETRY_TIMEOUT;
    else if(config->retry_connrefused &&
            (CURLE_COULDNT_CONNECT == result)) {
      long oserrno = 0;
      curl_easy_getinfo(curl, CURLINFO_OS_ERRNO, &oserrno);
      if(ECONNREFUSED == oserrno)
        retry = RETRY_CONNREFUSED;
    }
    else if((CURLE_OK == result) ||
            (config->failonerror &&
             (CURLE_HTTP_RETURNED_ERROR == result))) {


      long protocol = 0;
      curl_easy_getinfo(curl, CURLINFO_PROTOCOL, &protocol);
      if((protocol == CURLPROTO_HTTP) || (protocol == CURLPROTO_HTTPS)) {

        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response);

        switch(response) {
        case 408:
        case 429:
        case 500:
        case 502:
        case 503:
        case 504:
          retry = RETRY_HTTP;


          break;
        }
      }
    }
    else if(result) {
      long protocol = 0;

      curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response);
      curl_easy_getinfo(curl, CURLINFO_PROTOCOL, &protocol);

      if((protocol == CURLPROTO_FTP || protocol == CURLPROTO_FTPS) &&
         response / 100 == 4)


        retry = RETRY_FTP;
    }

    if(result && !retry && config->retry_all_errors)
      retry = RETRY_ALL_ERRORS;

    if(retry) {
      long sleeptime = 0;
      curl_off_t retry_after = 0;
      static const char * const m[]={
        NULL,
        "(retrying all errors)",
        ": timeout",
        ": connection refused",
        ": HTTP error",
        ": FTP error"
      };

      sleeptime = per->retry_sleep;
      if(RETRY_HTTP == retry) {
        curl_easy_getinfo(curl, CURLINFO_RETRY_AFTER, &retry_after);
        if(retry_after) {

          if(retry_after > LONG_MAX/1000)
            sleeptime = LONG_MAX;
          else
            sleeptime = (long)retry_after * 1000;


          if(config->retry_maxtime) {
            curl_off_t seconds = tvdiff(tvnow(), per->retrystart)/1000;

            if((CURL_OFF_T_MAX - retry_after < seconds) ||
               (seconds + retry_after > config->retry_maxtime)) {
              warnf(config->global, "The Retry-After: time would "
                    "make this command line exceed the maximum allowed time "
                    "for retries.");
              goto noretry;
            }
          }
        }
      }
      warnf(config->global, "Problem %s. "
            "Will retry in %ld seconds. "
            "%ld retries left.\n",
            m[retry], sleeptime/1000L, per->retry_numretries);

      per->retry_numretries--;
      if(!config->retry_delay) {
        per->retry_sleep *= 2;
        if(per->retry_sleep > RETRY_SLEEP_MAX)
          per->retry_sleep = RETRY_SLEEP_MAX;
      }
      if(outs->bytes && outs->filename && outs->stream) {
        int rc;


        if(!global->mute)
          fprintf(global->errors, "Throwing away %"
                  CURL_FORMAT_CURL_OFF_T " bytes\n",
                  outs->bytes);
        fflush(outs->stream);

#ifdef HAVE_FTRUNCATE
        if(ftruncate(fileno(outs->stream), outs->init)) {


          if(global->showerror)
            fprintf(global->errors,
                    "curl: (23) Failed to truncate file\n");
          return CURLE_WRITE_ERROR;
        }


        rc = fseek(outs->stream, 0, SEEK_END);
#else


        rc = fseek(outs->stream, (long)outs->init, SEEK_SET);
#endif
        if(rc) {
          if(global->showerror)
            fprintf(global->errors,
                    "curl: (23) Failed seeking to end of file\n");
          return CURLE_WRITE_ERROR;
        }
        outs->bytes = 0;
      }
      *retryp = TRUE;
      *delay = sleeptime;
      return CURLE_OK;
    }
  }
  noretry:

  if((global->progressmode == CURL_PROGRESS_BAR) &&
     per->progressbar.calls)


    fputs("\n", per->progressbar.out);


  if(outs->fopened && outs->stream) {
    int rc = fclose(outs->stream);
    if(!result && rc) {

      result = CURLE_WRITE_ERROR;
      if(global->showerror)
        fprintf(global->errors, "curl: (%d) Failed writing body\n", result);
    }
    if(result && config->rm_partial) {
      notef(global, "Removing output file: %s\n", outs->filename);
      unlink(outs->filename);
    }
  }


  if(!result && config->remote_time && outs->s_isreg && outs->filename) {

    curl_off_t filetime = -1;
    curl_easy_getinfo(curl, CURLINFO_FILETIME_T, &filetime);
    setfiletime(filetime, outs->filename, global);
  }


  if(config->writeout)
    ourWriteOut(config->writeout, per, result);


  if(per->heads.fopened && per->heads.stream)
    fclose(per->heads.stream);

  if(per->heads.alloc_filename)
    Curl_safefree(per->heads.filename);

  if(per->etag_save.fopened && per->etag_save.stream)
    fclose(per->etag_save.stream);

  if(per->etag_save.alloc_filename)
    Curl_safefree(per->etag_save.filename);

  curl_easy_cleanup(per->curl);
  if(outs->alloc_filename)
    free(outs->filename);
  free(per->this_url);
  free(per->outfile);
  free(per->uploadfile);

  return result;
}
