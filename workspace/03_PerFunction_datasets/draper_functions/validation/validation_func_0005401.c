CSFD(bool update)
{
   Update = false;
   ifstream in((Dir+"wh.txt").c_str());
   ReadVerify(in);
   seed1 = seed2 = seed3 = 0;
   char x; int n;
   for (n = 28; n >= 0; n -= 4) { in >> x; seed1 |= unhex(x, n); }
   for (n = 28; n >= 0; n -= 4) { in >> x; seed2 |= unhex(x, n); }
   for (n = 28; n >= 0; n -= 4) { in >> x; seed3 |= unhex(x, n); }
   ReadVerify(in);
   in.close();
   Update = update;
}
