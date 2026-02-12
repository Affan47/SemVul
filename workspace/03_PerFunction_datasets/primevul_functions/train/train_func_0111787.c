static void sweep2old (lua_State *L, GCObject **p) {
  GCObject *curr;
  while ((curr = *p) != NULL) {
    if (iswhite(curr)) {
      lua_assert(isdead(G(L), curr));
      *p = curr->next;
      freeobj(L, curr);
    }
    else {
      setage(curr, G_OLD);
      p = &curr->next;
    }
  }
}
