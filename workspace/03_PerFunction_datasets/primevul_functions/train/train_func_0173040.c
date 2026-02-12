char *month_name(int m)

{
   struct tm ts;
   static char name[32];

   memset(&ts, 0, sizeof(ts));
   ts.tm_mon = m;
   ts.tm_mday = 15;
   ts.tm_year = 2000;

   mktime(&ts);
   strftime(name, sizeof(name), "%B", &ts);
   return name;
}
