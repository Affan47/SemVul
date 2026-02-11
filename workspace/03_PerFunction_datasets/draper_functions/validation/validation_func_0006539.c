square_to_string(int square, char string[], int size) {

   ASSERT(square_is_ok(square));
   ASSERT(string!=NULL);
   ASSERT(size>=3);

   if (size < 3) return false;

   string[0] = 'a' + square_file(square);
   string[1] = '1' + square_rank(square);
   string[2] = '\0';

   return true;
}
