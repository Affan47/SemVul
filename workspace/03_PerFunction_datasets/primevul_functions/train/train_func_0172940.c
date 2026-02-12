char *param_in_str(char *str, char *param) {
   char *p;

   p = str;
   do {
      if (stristr(p, param) == NULL)
         return NULL;

      p = stristr(p, param);


      if (*(p + strlen(param)) != '=') {
         p += strlen(param);
         continue;
      }


      if (p > str + 1 && *(p - 1) == '=') {
         p += strlen(param);
         continue;
      }

      if (*p == 0)
         return NULL;

      return p;

   } while (1);
}
