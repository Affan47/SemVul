int is_logbook(char *logbook) {
   char str[256];

   if (strieq(logbook, "global"))
      return 0;


   strlcpy(str, logbook, sizeof(str));
   str[7] = 0;
   return !strieq(str, "global ");
}
