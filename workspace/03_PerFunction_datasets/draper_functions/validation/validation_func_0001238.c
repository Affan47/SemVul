mystrdup(const char * s)
 {
   char * d = NULL;
   if (s) {
      size_t sl = strlen(s)+1;
      d = (char *) malloc(sl);
      if (d) {
         memcpy(d,s,sl);
      } else {
         HUNSPELL_WARNING(stderr, "Can't allocate memory.\n");
      }
   }
   return d;
 }
