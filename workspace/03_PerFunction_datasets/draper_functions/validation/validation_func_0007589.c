meta(char buffer[20]){
  char* p = strchr(buffer, '*');
  if(p != NULL) return 1;
  p = strchr(buffer, '-');
  if(p != NULL) return 1;
  return 0;
}
