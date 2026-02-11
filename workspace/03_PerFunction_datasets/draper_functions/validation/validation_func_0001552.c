wskip(s)
char *s;
   {
   char c;

   while (isspace(c = *s))
      s++;
   if (c == '#')
      while ((c = *++s) != 0)
         ;
   return s;
   }
