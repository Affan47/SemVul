parseicon(char *tline)
{
  int len;
  struct iconfile *tmp;
  char *ptr, *start, *end;

  tmp = (struct iconfile *)safemalloc(sizeof(struct iconfile));


   tmp->name = stripcpy(tline);
   if(tmp->name == NULL){
     free(tmp);
     return;
   }


   while((*tline != '"')&&(tline != NULL))
     tline++;
    if(*tline != 0)
      tline++;
   while((*tline != '"')&&(tline != NULL))
     tline++;
   if(*tline == 0){
     free(tmp);
     return;
   }
   tline++;


   while(isspace((unsigned char)*tline)&&(*tline != '\n')&&(*tline != 0))
     tline++;
   start = tline;
   end = tline;
   while(!isspace((unsigned char)*end)&&(*end != '\n')&&(*end != 0))
     end++;
   len = end - start;
   ptr = safemalloc(len+1);
   strncpy(ptr, start, len);
   ptr[len] = 0;
   tmp->iconfile = ptr;

  if (strcmp(tmp->name, "*") == 0)
    DefaultIcon = tmp;

  tmp->next = NULL;

  if (IconListHead == NULL)
    IconListHead = IconListTail = tmp;
  else{
    IconListTail->next = tmp;
    IconListTail = tmp;
  }
}
