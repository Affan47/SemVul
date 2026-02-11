comment_add(char **comments, int* length,
                        const char *tag, const char *val)
{
  char* p=*comments;
  int vendor_length=readint(p, 0);
  int user_comment_list_length=readint(p, 4+vendor_length);
  int tag_len=(tag?strlen(tag):0);
  int val_len=strlen(val);
  int len=(*length)+4+tag_len+val_len;

  p=realloc(p, len);
  if(p==NULL){
  }

  writeint(p, *length, tag_len+val_len);
  if(tag) memcpy(p+*length+4, tag, tag_len);
  memcpy(p+*length+4+tag_len, val, val_len);
  writeint(p, 4+vendor_length, user_comment_list_length+1);

  *comments=p;
  *length=len;
}
