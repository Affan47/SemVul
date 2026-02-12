void remove_crlf(char *buffer) {
   char *p;


   p = buffer;
   while ((p = strstr(p, "\r\n")) != NULL) {
      memmove(p, p + 1, strlen(p + 1) + 1);
   }
}
