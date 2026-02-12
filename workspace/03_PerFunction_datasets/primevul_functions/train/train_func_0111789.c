static void genstep (lua_State *L, global_State *g) {
  if (g->lastatomic != 0)
    stepgenfull(L, g);
  else {
    lu_mem majorbase = g->GCestimate;
    lu_mem majorinc = (majorbase / 100) * getgcparam(g->genmajormul);
    if (g->GCdebt > 0 && gettotalbytes(g) > majorbase + majorinc) {
      lu_mem numobjs = fullgen(L, g);
      if (gettotalbytes(g) < majorbase + (majorinc / 2)) {


        setminordebt(g);
      }
      else {
        g->lastatomic = numobjs;
        setpause(g);
      }
    }
    else {
      youngcollection(L, g);
      setminordebt(g);
      g->GCestimate = majorbase;
    }
  }
  lua_assert(isdecGCmodegen(g));
}
