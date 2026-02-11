parsemouse(char *tline)
{
  struct mousefunc *f = NULL;
  int len;
  int n;
  int b;
  char *ptr,*start,*end,*tmp;

  f = (struct mousefunc *)safemalloc(sizeof(struct mousefunc));
  memset(f, 0, sizeof(struct mousefunc));


  while(isspace((unsigned char)*tline)&&(*tline != '\n')&&(*tline != 0))
    tline++;
  start = tline;
  end = tline;
  while((!isspace((unsigned char)*end))&&(*end!='\n')&&(*end!=0))
    end++;
  n = sscanf(start, "%d", &b);
  if (n > 0 && b >= 0 && b <= NUMBER_OF_EXTENDED_MOUSE_BUTTONS)
    f->mouse = b;
  else
    f->mouse = -1;

  tline = end;

  while(isspace((unsigned char)*tline)&&(*tline != '\n')&&(*tline != 0))
    tline++;
  start = tline;
  end = tline;
  while((!isspace((unsigned char)*end))&&(*end!='\n')&&(*end!=0))
    end++;
  if (strncasecmp(start, "Click", 5) == 0)
    f->type = CLICK;
  else if (strncasecmp(start, "DoubleClick", 11) == 0)
  {
    f->type = DOUBLE_CLICK;
    have_double_click = True;
  }


  tline = end;

  while(isspace((unsigned char)*tline)&&(*tline != '\n')&&(*tline != 0))
    tline++;
  start = tline;
  end = tline;
  tmp = tline;
  while((*tmp!='\n')&&(*tmp!=0)){
    if (!isspace((unsigned char)*tmp))
      end = tmp;
    tmp++;
  }
  end++;
  len = end - start;
  ptr = safemalloc(len+1);
  strncpy(ptr, start, len);
  ptr[len] = 0;
  f->action = ptr;
  f->next = MouseActions;
  MouseActions = f;
}
