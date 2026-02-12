char *trim_whitespace(char *str) {
char *dud = str;
int i;


   while( (int)*dud && isspace((int)*dud) )
      ++dud;

   i = strlen(dud) - 1;
   while( i>=0 && isspace((int)dud[i]) )
      --i;
   dud[i+1] = 0;
   return dud;
}
