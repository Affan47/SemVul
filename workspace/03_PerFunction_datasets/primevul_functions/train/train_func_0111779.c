static lu_mem singlestep (lua_State *L) {
  global_State *g = G(L);
  switch (g->gcstate) {
    case GCSpause: {
      restartcollection(g);
      g->gcstate = GCSpropagate;
      return 1;
    }
    case GCSpropagate: {
      if (g->gray == NULL) {
        g->gcstate = GCSenteratomic;
        return 0;
      }
      else
        return propagatemark(g);
    }
    case GCSenteratomic: {
      lu_mem work = atomic(L);
      entersweep(L);
      g->GCestimate = gettotalbytes(g);  ;
      return work;
    }
    case GCSswpallgc: {
      return sweepstep(L, g, GCSswpfinobj, &g->finobj);
    }
    case GCSswpfinobj: {
      return sweepstep(L, g, GCSswptobefnz, &g->tobefnz);
    }
    case GCSswptobefnz: {
      return sweepstep(L, g, GCSswpend, NULL);
    }
    case GCSswpend: {
      checkSizes(L, g);
      g->gcstate = GCScallfin;
      return 0;
    }
    case GCScallfin: {
      if (g->tobefnz && !g->gcemergency) {
        int n = runafewfinalizers(L, GCFINMAX);
        return n * GCFINALIZECOST;
      }
      else {
        g->gcstate = GCSpause;
        return 0;
      }
    }
    default: lua_assert(0); return 0;
  }
}
