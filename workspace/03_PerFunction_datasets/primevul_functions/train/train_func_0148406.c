static int fits_scanfdouble (const char *buf, double *value)
{
 int retval = 0;
 gchar *bufcopy = g_strdup (buf);


 if ( bufcopy )
 {
   gchar *bufptr = bufcopy;


   g_strchug (bufcopy);


   if ( (*bufptr == '-') || (*bufptr == '+') )
     bufptr++;


   if ( (bufptr[0] == '0') && (g_ascii_toupper (bufptr[1]) == 'X') )
   {
     *value = 0.0;
     retval = 1;
   }
   else
   {
     if ( *bufptr == '.' )
       bufptr++;

     if (g_ascii_isdigit (*bufptr))
     {
       gchar *endptr;
       gdouble gvalue = g_ascii_strtod (bufcopy, &endptr);
       if ( errno == 0 )
       {
         *value = gvalue;
         retval = 1;
       }
     }
   }
   g_free (bufcopy);
 }
 return retval;
}
