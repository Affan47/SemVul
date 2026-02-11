d_def_50_(fortint * outputArray, unsigned char * gribSection1) {


int loop;
fortint * n = outputArray;
unsigned char * p = gribSection1;

  decodeMarsPart(n,p);
  p += 9;
  n += 5;

  *n++ = ONEBYTEINT(p);p++;
  *n++ = ONEBYTEINT(p);p++;
  *n++ = ONEBYTEINT(p);p++;

  *n++ = FOURBYTEINT(p);
  p += 4;
  *n++ = FOURBYTEINT(p);
  p += 4;
  *n++ = FOURBYTEINT(p);
  p += 4;
  *n++ = FOURBYTEINT(p);
  p += 4;


  *n++ = ONEBYTEINT(p);p++;
  *n++ = ONEBYTEINT(p);p++;

  for( loop = 0; loop < 10; loop++ )
    *n++ = 0;

  p += 46;


  for( loop = 0; loop < 46; loop++) {
    *n++ = FOURBYTEINT(p);
    p += 4;
  }

  return (fortint) (n - outputArray);
}
