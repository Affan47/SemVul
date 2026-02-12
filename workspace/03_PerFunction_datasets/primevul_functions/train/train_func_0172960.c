void highlight_searchtext(regex_t *re_buf, char *src, char *dst, int hidden) {
   char *pt, *pt1;
   int size, status;
   regmatch_t pmatch[10];

   dst[0] = 0;
   pt = src;
   pt1 = dst;
   do {
      status = regexec(re_buf, pt, 10, pmatch, 0);
      if (status != REG_NOMATCH) {
         size = pmatch[0].rm_so;


         if (pmatch[0].rm_eo - pmatch[0].rm_so == 0) {
            status = REG_NOMATCH;
            strcpy(pt1, pt);
            break;
         }

         memcpy(pt1, pt, size);
         pt1 += size;
         pt += size;


         if (hidden)
            strcpy(pt1, "\001B\004style=\003color:black;background-color:#ffff66\003\002");
         else
            strcpy(pt1, "<B style=\"color:black;background-color:#ffff66\">");

         pt1 += strlen(pt1);


         size = pmatch[0].rm_eo - pmatch[0].rm_so;
         memcpy(pt1, pt, size);
         pt1 += size;
         pt += size;


         if (hidden)
            strcpy(pt1, "\001/B\002");
         else
            strcpy(pt1, "</B>");
         pt1 += strlen(pt1);
      }
   } while (status != REG_NOMATCH);

   strcpy(pt1, pt);
}
