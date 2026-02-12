void *xrealloc(void *pointer, size_t bytes) {
   char *temp;
   int old_size;


   if (bytes & 3)
      bytes += 4 - (bytes & 3);

   if (pointer == NULL)
      return xmalloc(bytes);


   temp = pointer;
   assert(*((unsigned int *) (temp - 4)) == 0xdeadc0de);
   old_size = *((unsigned int *) (temp - 8));
   assert(*((unsigned int *) (temp + old_size)) == 0xdeadc0de);

   temp = (char *) realloc(temp - 8, bytes + 12);

   if (temp == 0)
      memory_error_and_abort("xrealloc");


   *(unsigned int *) (temp + 0) = bytes;
   *(unsigned int *) (temp + 4) = 0xdeadc0de;
   *(unsigned int *) (temp + bytes + 8) = 0xdeadc0de;

   return (temp + 8);
}
