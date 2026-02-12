static void hufCanonicalCodeTable(long long hcode[HUF_ENCSIZE]) {
  long long n[59];


  for (int i = 0; i <= 58; ++i) n[i] = 0;

  for (int i = 0; i < HUF_ENCSIZE; ++i) n[hcode[i]] += 1;


  long long c = 0;

  for (int i = 58; i > 0; --i) {
    long long nc = ((c + n[i]) >> 1);
    n[i] = c;
    c = nc;
  }


  for (int i = 0; i < HUF_ENCSIZE; ++i) {
    int l = static_cast<int>(hcode[i]);

    if (l > 0) hcode[i] = l | (n[l]++ << 6);
  }
}
