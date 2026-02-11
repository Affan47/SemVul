STRset(String *st, char *str)
{
     register int len;


     if (str == NULL) {
	  STRinit(st);
	  return;
     }


     if (st->len < 0)
	  st->len = -st->len;

     if (*str == '\0')
	  len = 1;
     else
	  len = strlen(str)+1;


     if (st->data == NULL) {
	  st->data = (char *) malloc(sizeof(char*) * len);
	  st->len = len;
     }


     else if (STRsize(st) < len) {
	  char *temp;

	  temp = (char *) realloc(st->data, sizeof(char) * len);

	  if (temp == NULL)
	       perror("realloc failed...");

	  st->data = temp;
	  st->len  = len;
     }

     strcpy(st->data, str);
}
