get_modifier(char *str, char *num, int num_len, char *mod, int mod_len)
{
   int i, len, num_begin, num_end, mod_begin, mod_end;

   strip_trailing_junk(str);
   len = strlen(str);

   for (i=0; i<len; i++) {
      if (!B_ISSPACE(str[i])) {
         break;
      }
   }
   num_begin = i;


   for ( ; i<len; i++) {
      if (!B_ISDIGIT(str[i]) && str[i] != '.') {
         break;
      }
   }
   num_end = i;
   if (num_len > (num_end - num_begin + 1)) {
      num_len = num_end - num_begin + 1;
   }
   if (num_len == 0) {
      return false;
   }

   for ( ; i<len; i++) {
      if (!B_ISSPACE(str[i])) {
         break;
      }
   }
   mod_begin = i;
   for ( ; i<len; i++) {
      if (!B_ISALPHA(str[i])) {
         break;
      }
   }
   mod_end = i;
   if (mod_len > (mod_end - mod_begin + 1)) {
      mod_len = mod_end - mod_begin + 1;
   }
   Dmsg5(900, "str=%s: num_beg=%d num_end=%d mod_beg=%d mod_end=%d\n",
      str, num_begin, num_end, mod_begin, mod_end);
   bstrncpy(num, &str[num_begin], num_len);
   bstrncpy(mod, &str[mod_begin], mod_len);
   if (!is_a_number(num)) {
      return false;
   }
   bstrncpy(str, &str[mod_end], len);
   Dmsg2(900, "num=%s mod=%s\n", num, mod);

   return true;
}
