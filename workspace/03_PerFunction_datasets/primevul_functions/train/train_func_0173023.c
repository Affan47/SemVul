void *xcalloc(size_t count, size_t bytes) {
   char *temp;


   if (bytes & 3)
      bytes += 4 - (bytes & 3);

   temp = (char *) malloc(count * bytes + 12);
   if (temp == 0)
      memory_error_and_abort("xcalloc");
   memset(temp, 0, count * bytes + 12);


   *(unsigned int *) (temp + 0) = count * bytes;
   *(unsigned int *) (temp + 4) = 0xdeadc0de;
   *(unsigned int *) (temp + count * bytes + 8) = 0xdeadc0de;

   return (temp + 8);
}
