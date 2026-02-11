rec1(struct child *c)
{
  int i;
  double t0 = now(), t1;

  srandom(kvtest_first_seed + c->childno);

  for(i = 0; !timeout[0]; i++){
    char key[512], val[512];
    long x = random();
    sprintf(key, "%ld-%d-%d", x, i, c->childno);
    sprintf(val, "%ld", x);
    aput(c, Str(key), Str(val));
  }
  checkasync(c, 2);
  t1 = now();

  fprintf(stderr, "child %d: done %d %.0f put/s\n",
          c->childno,
          i,
          i / (t1 - t0));
  printf("%.0f\n", i / (t1 - t0));
}
