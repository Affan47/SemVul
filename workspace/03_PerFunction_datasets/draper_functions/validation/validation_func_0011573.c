ParseHTTPVersion(const std::string& s,int& major,int& minor) {
  major=0; minor=0;
  const char* p = s.c_str();
  if(strncasecmp(p,"HTTP/",5) != 0) return false;
  p+=5;
  char* e;
  major=strtol(p,&e,10);
  if(*e != '.') { major=0; return false; };
  p=e+1;
  minor=strtol(p,&e,10);
  if(*e != 0) { major=0; minor=0; return false; };
  return true;
}
