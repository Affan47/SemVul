oauth_escape_shell (const char *cmd) {
  char *esc = xstrdup(cmd);
  char *tmp = esc;
  int idx;
  while ((tmp=strchr(tmp,'\''))) {
    idx = tmp-esc;
    esc=(char*)xrealloc(esc,(strlen(esc)+5)*sizeof(char));
    memmove(esc+idx+4,esc+idx+1, strlen(esc+idx));
    esc[idx+1]='\\'; esc[idx+2]='\''; esc[idx+3]='\'';
    tmp=esc+(idx+4);
  }


  return esc;
}
