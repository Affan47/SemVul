static void setpause (global_State *g) {
  l_mem threshold, debt;
  int pause = getgcparam(g->gcpause);
  l_mem estimate = g->GCestimate / PAUSEADJ;
  lua_assert(estimate > 0);
  threshold = (pause < MAX_LMEM / estimate)
            ? estimate * pause
            : MAX_LMEM;
  debt = gettotalbytes(g) - threshold;
  if (debt > 0) debt = 0;
  luaE_setdebt(g, debt);
}
