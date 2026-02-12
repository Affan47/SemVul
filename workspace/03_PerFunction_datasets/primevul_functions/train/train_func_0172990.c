void strsubst_list(char *string, int size, char name[][NAME_LENGTH], char value[][NAME_LENGTH], int n)

{
   int i, j;
   char tmp[2 * NAME_LENGTH], str[2 * NAME_LENGTH], uattr[2 * NAME_LENGTH], *ps, *pt, *p, result[10000];

   pt = tmp;
   ps = string;
   for (p = strchr(ps, '$'); p != NULL; p = strchr(ps, '$')) {


      j = (int) (p - ps);
      if (j >= (int) sizeof(tmp))
         return;
      memcpy(pt, ps, j);
      pt += j;
      p++;


      strlcpy(str, p, sizeof(str));
      for (j = 0; j < (int) strlen(str); j++)
         str[j] = toupper(str[j]);


      if (strncmp(str, "SHELL(", 6) == 0) {
         strlcpy(pt, "$shell(", sizeof(tmp) - (pt - tmp));
         ps += 7;
         pt += 7;
         continue;
      }


      for (i = 0; i < n; i++) {
         strlcpy(uattr, name[i], sizeof(uattr));
         for (j = 0; j < (int) strlen(uattr); j++)
            uattr[j] = toupper(uattr[j]);

         if (strncmp(str, uattr, strlen(uattr)) == 0)
            break;
      }


      if (i < n) {
         strlcpy(pt, value[i], sizeof(tmp) - (pt - tmp));
         pt += strlen(pt);
         ps = p + strlen(uattr);
      } else {
         *pt++ = '$';
         ps = p;
      }
   }


   strlcpy(pt, ps, sizeof(tmp) - (pt - tmp));
   strlcpy(string, tmp, size);


   pt = tmp;
   ps = string;
   for (p = strchr(ps, '$'); p != NULL; p = strchr(ps, '$')) {


      j = (int) (p - ps);
      if (j >= (int) sizeof(tmp))
         return;
      memcpy(pt, ps, j);
      pt += j;
      p++;


      strlcpy(str, p, sizeof(str));
      for (j = 0; j < (int) strlen(str); j++)
         str[j] = toupper(str[j]);

      if (strncmp(str, "SHELL(", 6) == 0) {
         ps += 7;
         if (strrchr(p, '\"')) {
            ps += strrchr(p, '\"') - p - 5;
            if (strchr(ps, ')'))
               ps = strchr(ps, ')') + 1;
         } else {
            if (strchr(ps, ')'))
               ps = strchr(ps, ')') + 1;
         }

         if (str[6] == '"') {
            strcpy(str, p + 7);
            if (strrchr(str, '\"'))
               *strrchr(str, '\"') = 0;
         } else {
            strcpy(str, p + 6);
            if (strrchr(str, ')'))
               *strrchr(str, ')') = 0;
         }

         if (!enable_execute) {
            strlcpy(result, loc("Shell execution not enabled via -x flag"), sizeof(result));
            eprintf("Shell execution not enabled via -x flag.\n");
         } else
            my_shell(str, result, sizeof(result));

         strlcpy(pt, result, sizeof(tmp) - (pt - tmp));
         pt += strlen(pt);
      } else {
         *pt++ = '$';
         ps = p;
      }
   }


   strlcpy(pt, ps, sizeof(tmp) - (pt - tmp));


   strlcpy(string, tmp, size);
}
