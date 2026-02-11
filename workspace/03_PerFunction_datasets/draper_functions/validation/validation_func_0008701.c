md_handle_input()
{
  int res;

  if(md_read(&res, sizeof(res))!=sizeof(res))
    return -1;
  if(res>=0) {
    if(!res)
      return 0;
    md_int_load(res);
    return 0;
  } else {
    res=~res;
    if(!res)
      return 0;
    return md_get_async(res);
  }
}
