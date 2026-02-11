Find(int x) {
  return x == l[x] ? x : (l[x] = Find(l[x]));
}
