void Curl_expire_latest(struct Curl_easy *data, long milli)
{
  struct timeval *expire = &data->state.expiretime;

  struct timeval set;

  set = Curl_tvnow();
  set.tv_sec += milli / 1000;
  set.tv_usec += (milli % 1000) * 1000;

  if(set.tv_usec >= 1000000) {
    set.tv_sec++;
    set.tv_usec -= 1000000;
  }

  if(expire->tv_sec || expire->tv_usec) {


    long diff = curlx_tvdiff(set, *expire);
    if(diff > 0)

      return;
  }


  Curl_expire(data, milli);
}
