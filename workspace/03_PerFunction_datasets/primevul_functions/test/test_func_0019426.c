output_expected(const char* url, const char* uploadfile)
{
  if(!uploadfile)
    return TRUE;
  if(checkprefix("http://", url) || checkprefix("https://", url))
    return TRUE;

  return FALSE;
}
