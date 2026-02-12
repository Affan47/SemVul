static void clearkey (Node *n) {
  lua_assert(isempty(gval(n)));
  if (keyiswhite(n))
    setdeadkey(n);
}
