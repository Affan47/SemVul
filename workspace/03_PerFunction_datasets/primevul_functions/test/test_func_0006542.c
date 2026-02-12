void Curl_flush_cookies(struct Curl_easy *data, bool cleanup)
{
  CURLcode res;

  if(data->set.str[STRING_COOKIEJAR]) {
    if(data->state.cookielist) {


      Curl_cookie_loadfiles(data);
    }

    Curl_share_lock(data, CURL_LOCK_DATA_COOKIE, CURL_LOCK_ACCESS_SINGLE);


    res = cookie_output(data, data->cookies, data->set.str[STRING_COOKIEJAR]);
    if(res)
      infof(data, "WARNING: failed to save cookies in %s: %s",
            data->set.str[STRING_COOKIEJAR], curl_easy_strerror(res));
  }
  else {
    if(cleanup && data->state.cookielist) {


      curl_slist_free_all(data->state.cookielist);
      data->state.cookielist = NULL;
    }
    Curl_share_lock(data, CURL_LOCK_DATA_COOKIE, CURL_LOCK_ACCESS_SINGLE);
  }

  if(cleanup && (!data->share || (data->cookies != data->share->cookies))) {
    Curl_cookie_cleanup(data->cookies);
    data->cookies = NULL;
  }
  Curl_share_unlock(data, CURL_LOCK_DATA_COOKIE);
}
