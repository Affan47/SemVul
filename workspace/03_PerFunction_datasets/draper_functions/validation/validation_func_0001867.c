cpyStr(char** dest, const char* src) {
  if (*dest!=NULL) free(*dest);
  *dest=(char*)malloc((strlen(src)+1)*sizeof(char));
  if (*dest==NULL) oom();
  strcpy(*dest,src);
}
