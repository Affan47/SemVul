validRlogin(rlogin)
char *rlogin;
{
   char line[80] ;
   FILE *fp ;
   char *tmp, *user, *rhost ;

   if ((fp = fopen(RLOGIN_FILE, "r")) == NULL)
      return 0 ;

   user = line ;
   while (fgets(line, sizeof(line), fp) != NULL)
    {
       if ((tmp = strchr(line, '@')) == NULL)
          continue ;
       *tmp = '\0' ;
       if (strcmp(user, rlogin))
          continue ;
       rhost = tmp + 1 ;
       if ((tmp = strchr(rhost, '\n')) != NULL)
          *tmp = '\0' ;
        {
       if (validRhost(rhost))
           fclose(fp) ;
           return 1 ;
        }
    }
   fclose(fp) ;
   return 0 ;
}
