static int stbi__addsizes_valid(int a, int b)
{
   if (b < 0) return 0;


   return a <= INT_MAX - b;
}
