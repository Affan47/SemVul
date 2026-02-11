u1(struct child *c)
{
  int i, n;
  double t0 = now();

  srandom(kvtest_first_seed + c->childno);

  for(i = 0; i < 10000000; i++){
    char key[512], val[512];
    long x = random() % 10000000;
    sprintf(key, "%ld", x);
    sprintf(val, "%ld", x + 1);
    aput(c, Str(key), Str(val));
  }
  n = i;

  checkasync(c, 2);

  double t1 = now();
  Json result = Json().set("total", (long) (n / (t1 - t0)))
    .set("puts", n)
    .set("puts_per_sec", n / (t1 - t0));
  printf("%s\n", result.unparse().c_str());
}
