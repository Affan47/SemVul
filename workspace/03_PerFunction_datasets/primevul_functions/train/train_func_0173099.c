void stou(char *str)

{
   int i;

   for (i = 0; i < (int) strlen(str); i++)
      if (!isalnum(str[i]))
         str[i] = '_';
}
