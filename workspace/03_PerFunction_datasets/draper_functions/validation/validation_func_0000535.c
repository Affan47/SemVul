fd_compare(const void* fd1, const void* fd2) {
   int* i1 = (int*) fd1;
   int* i2 = (int*) fd2;


   if (i1 == NULL || i2 == NULL) {
      if (i1 > i2) {
         return 1;
      }
      if (i1 < i2) {
         return -1;
      }
      return 0;
   }

   if (*i1 > *i2) {
      return 1;
   }
   if (*i1 < *i2) {
      return -1;
   }
   return 0;
}
