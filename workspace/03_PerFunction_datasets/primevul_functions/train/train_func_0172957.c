void adjust_crlf(char *buffer, int bufsize) {
   char *p;
   UNUSED(bufsize);

#ifdef OS_UNIX


   p = buffer;
   while ((p = strstr(p, "\r\n")) != NULL) {
      memmove(p, p + 1, strlen(p + 1) + 1);
   }
#else

                                                                                                                           char *tmpbuf;

   assert(bufsize);
   tmpbuf = xmalloc(bufsize);


   p = buffer;
   while ((p = strstr(p, "\n")) != NULL) {

      if (p > buffer && *(p - 1) == '\r') {
         p++;
         continue;
      }

      if ((int) strlen(buffer) + 2 >= bufsize) {
         xfree(tmpbuf);
         return;
      }

      strlcpy(tmpbuf, p, bufsize);
      *(p++) = '\r';
      strlcpy(p, tmpbuf, bufsize - (p - buffer));
      p++;
   }

   xfree(tmpbuf);
#endif
}
