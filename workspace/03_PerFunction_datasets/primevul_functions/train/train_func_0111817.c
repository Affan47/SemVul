static void finishgencycle (lua_State *L, global_State *g) {
  correctgraylists(g);
  checkSizes(L, g);
  g->gcstate = GCSpropagate;
  if (!g->gcemergency)
    callallpendingfinalizers(L);
}
