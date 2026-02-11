operator/(Real s, Random& rv)
{
   ReciprocalRandom* r = new ReciprocalRandom(rv, s);
   if (!r) ErrorNoSpace(); return *r;
}
