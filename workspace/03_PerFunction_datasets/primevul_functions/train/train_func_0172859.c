void *xmalloc(size_t bytes) {
   char *temp;


   if (bytes & 3)
      bytes += 4 - (bytes & 3);

   temp = (char *) malloc(bytes + 12);
   if (temp == 0)
      memory_error_and_abort("xmalloc");


   *(unsigned int *) (temp + 0) = bytes;
   *(unsigned int *) (temp + 4) = 0xdeadc0de;
   *(unsigned int *) (temp + bytes + 8) = 0xdeadc0de;

   return (temp + 8);
}
