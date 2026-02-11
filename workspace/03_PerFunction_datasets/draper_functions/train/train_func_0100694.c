utl_GetRHeaderString (str, separ)

char *str  ;
char  separ;

  {
  char *head  = NULL;
  int   found = 0   ;
  int   len   ;
  int   i     ;

  if (str != NULL)
    {
    len = strlen (str);

    for (i=len-1 ; i>0 ; i--)
      {
      if (str [i] == separ)
        {
        found = 1;
        break;
        }
      }

    if (found != 0)
      head = utl_SaveNString (str, i);
    else
      head = utl_SaveString  (str   );
    }

  return (head);
  }
