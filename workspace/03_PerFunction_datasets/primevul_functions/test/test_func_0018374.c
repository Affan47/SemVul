static void checktoclose (FuncState *fs, int level) {
  if (level != -1) {
    marktobeclosed(fs);
    luaK_codeABC(fs, OP_TBC, reglevel(fs, level), 0, 0);
  }
}
