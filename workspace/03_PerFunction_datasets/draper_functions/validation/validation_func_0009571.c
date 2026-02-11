parseint(const char *s, int *n)
{
     int sign = 1;

     *n = 0;

     if (*s == '-') {
	  sign = -1;
	  ++s;
     } else if (*s == '+') {
	  sign = +1;
	  ++s;
     }

     BENCH_ASSERT(isdigit(*s));
     while (isdigit(*s)) {
	  *n = *n * 10 + (*s - '0');
	  ++s;
     }

     *n *= sign;

     if (*s == 'k' || *s == 'K') {
	  *n *= 1024;
	  ++s;
     }

     if (*s == 'm' || *s == 'M') {
	  *n *= 1024 * 1024;
	  ++s;
     }

     return s;
}
