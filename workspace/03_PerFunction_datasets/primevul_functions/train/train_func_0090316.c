static CURLcode run_all_transfers(struct GlobalConfig *global,
                                  CURLSH *share,
                                  CURLcode result)
{

  bool orig_noprogress = global->noprogress;
  bool orig_isatty = global->isatty;
  struct per_transfer *per;


  if(!result) {
    if(global->parallel)
      result = parallel_transfers(global, share);
    else
      result = serial_transfers(global, share);
  }


  for(per = transfers; per;) {
    bool retry;
    long delay;
    CURLcode result2 = post_per_transfer(global, per, result, &retry, &delay);
    if(!result)

      result = result2;


    clean_getout(per->config);

    per = del_per_transfer(per);
  }


  global->noprogress = orig_noprogress;
  global->isatty = orig_isatty;


  return result;
}
