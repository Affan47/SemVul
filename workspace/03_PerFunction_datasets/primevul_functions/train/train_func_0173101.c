time_t convert_date(char *date_string) {

   int year, month, day;
   char *p, str[256];
   struct tm tms;
   time_t ltime;

   strlcpy(str, date_string, sizeof(str));
   month = day = year = 0;

   if (strchr(str, '[')) {
      ltime = atoi(strchr(str, '[') + 1);
      return ltime;
   } else if (strchr(str, '/')) {

      p = strtok(str, "/");
      if (p) {
         month = atoi(p);
         p = strtok(NULL, "/");
         if (p) {
            day = atoi(p);
            p = strtok(NULL, "/");
            if (p)
               year = atoi(p);
         }
      }
   } else if (strchr(str, '.')) {

      p = strtok(str, ".");
      if (p) {
         day = atoi(p);
         p = strtok(NULL, ".");
         if (p) {
            month = atoi(p);
            p = strtok(NULL, ".");
            if (p)
               year = atoi(p);
         }
      }
   } else
      return 0;


   if (year > 1900)
      year += 0;
   else if (year < 70)
      year += 2000;
   else if (year < 100)
      year += 1900;


   memset(&tms, 0, sizeof(struct tm));
   tms.tm_year = year - 1900;
   tms.tm_mon = month - 1;
   tms.tm_mday = day;
   tms.tm_hour = 12;

   ltime = mktime(&tms);

   return ltime;
}
