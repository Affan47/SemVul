power(int base, int exponent)
{
   if (exponent == 0)
      return 1;
   else if (exponent%2 == 0)
      return power(base, exponent/2) * power(base, exponent/2);
   else
      return base * power(base, exponent - 1);
}
