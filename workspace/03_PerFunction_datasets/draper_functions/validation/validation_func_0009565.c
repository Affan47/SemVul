readsig(a, b, sig)


int *a, *b;
char *sig;
{
  char *p;
  int t;

  p = sig;
  if ((int)*p == 'C') {
    *a = 4;
    *b = 4;
    return;
  };
  *a = readnump(&p);
  if ((int)*p != '/') {
    char msg[80];

    sprintf(msg, "Expecting / in time signature found %c!", *p);
    fatal_error(msg);
  };
  p = p + 1;
  *b = readnump(&p);
  if ((*a == 0) || (*b == 0)) {
    char msg[80];

    sprintf(msg, "%d/%d is not a valid time signature!", *a, *b);
    fatal_error(msg);
  };
  t = *b;
  while (t > 1) {
    if (t%2 != 0) {
      fatal_error("Bad key signature, divisor must be a power of 2!");
    }
    else {
      t = t/2;
    };
  };
}
