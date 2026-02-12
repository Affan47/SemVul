
    inline long gcd(long a, long b) {
      while (a) { const long c = a; a = b%a; b = c; }
      return b;
}
