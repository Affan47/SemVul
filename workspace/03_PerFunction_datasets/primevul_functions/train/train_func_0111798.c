static void markold (global_State *g, GCObject *from, GCObject *to) {
  GCObject *p;
  for (p = from; p != to; p = p->next) {
    if (getage(p) == G_OLD1) {
      lua_assert(!iswhite(p));
      if (isblack(p)) {
        black2gray(p);
        reallymarkobject(g, p);
      }
    }
  }
}
