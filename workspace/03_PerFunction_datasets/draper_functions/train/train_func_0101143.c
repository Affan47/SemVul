get_pref_hour_ampm(char *datef)
{
   const char *svalue;

   get_pref(PREF_TIME, NULL, &svalue);
   strncpy(datef, svalue, 2);
   datef[2]='\0';
   if (!strncasecmp(&(svalue[strlen(svalue)-2]), "%p", 2)) {
      strncpy(&(datef[2]), &(svalue[strlen(svalue)-2]), 2);
      datef[4]='\0';
   }
}
