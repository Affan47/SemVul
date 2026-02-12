static GCObject **sweepgen (lua_State *L, global_State *g, GCObject **p,
                            GCObject *limit) {
  static const lu_byte nextage[] = {
    G_SURVIVAL,
    G_OLD1,
    G_OLD1,
    G_OLD,
    G_OLD,
    G_TOUCHED1,
    G_TOUCHED2
  };
  int white = luaC_white(g);
  GCObject *curr;
  while ((curr = *p) != limit) {
    if (iswhite(curr)) {
      lua_assert(!isold(curr) && isdead(g, curr));
      *p = curr->next;
      freeobj(L, curr);
    }
    else {
      if (getage(curr) == G_NEW)
        curr->marked = cast_byte((curr->marked & maskgencolors) | white);
      setage(curr, nextage[getage(curr)]);
      p = &curr->next;
    }
  }
  return p;
}
