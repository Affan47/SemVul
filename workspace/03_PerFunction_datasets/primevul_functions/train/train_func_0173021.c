static int int_vasprintf(char **result, const char *format, va_list args) {
   const char *p = format;


   int total_width = strlen(format) + 1;
   va_list ap;

#ifdef va_copy
   va_copy(ap, args);
#else
   memcpy(&ap, &args, sizeof(va_list));
#endif

   while (*p != '\0') {
      if (*p++ == '%') {
         while (strchr("-+ #0", *p))
            ++p;
         if (*p == '*') {
            ++p;
            total_width += abs(va_arg(ap, int));
         } else
            total_width += strtoul(p, (char **) &p, 10);
         if (*p == '.') {
            ++p;
            if (*p == '*') {
               ++p;
               total_width += abs(va_arg(ap, int));
            } else
               total_width += strtoul(p, (char **) &p, 10);
         }
         while (strchr("hlL", *p))
            ++p;


         total_width += 30;
         switch (*p) {
            case 'd':
            case 'i':
            case 'o':
            case 'u':
            case 'x':
            case 'X':
            case 'c':
               (void) va_arg(ap, int);
               break;
            case 'f':
            case 'e':
            case 'E':
            case 'g':
            case 'G':
               (void) va_arg(ap, double);


               total_width += 307;
               break;
            case 's':
               total_width += strlen(va_arg(ap, char *));
               break;
            case 'p':
            case 'n':
               (void) va_arg(ap, char *);
               break;
         }
         p++;
      }
   }
#ifdef va_copy
   va_end(ap);
#endif
   *result = (char *) malloc(total_width);
   if (*result != NULL)
      return vsprintf(*result, format, args);
   else
      return -1;
}
