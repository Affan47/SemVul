IsHardClass(char *sp)

{ int i;

for (i = 2; CLASSTEXT[i] != '\0'; i++)
   {
   if (strcmp(CLASSTEXT[i],sp) == 0)
      {
      return(true);
      }
   }

for (i = 0; i < 7; i++)
   {
   if (strcmp(DAYTEXT[i],sp)==0)
      {
      return(false);
      }
   }

return(false);
}
