hash(const GURL & gurl)
{
  unsigned int retval;
  const GUTF8String s(gurl.get_string());
  const int len=s.length();
  if(len && (s[len-1] == '/'))
  {
	retval=hash(s.substr(0,len-1));
  }else
  {
    retval=hash(s);
  }
  return retval;
}
