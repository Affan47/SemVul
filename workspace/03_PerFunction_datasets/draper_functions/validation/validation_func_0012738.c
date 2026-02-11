luaV_concat (lua_State *L, int total, int last) {
  do {
    StkId top = L->base + last + 1;
    int n = 2;
    if (!tostring(L, top-2) || !tostring(L, top-1)) {
      if (!call_binTM(L, top-2, top-1, top-2, TM_CONCAT))
        luaG_concaterror(L, top-2, top-1);
    } else if (tsvalue(top-1)->tsv.len > 0) {

      lu_mem tl = cast(lu_mem, tsvalue(top-1)->tsv.len) +
                  cast(lu_mem, tsvalue(top-2)->tsv.len);
      char *buffer;
      int i;
      while (n < total && tostring(L, top-n-1)) {
        tl += tsvalue(top-n-1)->tsv.len;
        n++;
      }
      if (tl > MAX_SIZET) luaG_runerror(L, "string size overflow");
      buffer = luaZ_openspace(L, &G(L)->buff, tl);
      tl = 0;
      for (i=n; i>0; i--) {
        size_t l = tsvalue(top-i)->tsv.len;
        memcpy(buffer+tl, svalue(top-i), l);
        tl += l;
      }
      setsvalue2s(top-n, luaS_newlstr(L, buffer, tl));
    }
    total -= n-1;
    last -= n-1;
  } while (total > 1);
}
