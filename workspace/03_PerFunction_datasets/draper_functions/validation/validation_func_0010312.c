io_file_read(lua_State *L, FILE *fp, int start)
{
  int ok, n, nargs = (int)(L->top - L->base) - start;
  clearerr(fp);
  if (nargs == 0) {
    ok = io_file_readline(L, fp, 1);
    n = start+1;
  } else {

    luaL_checkstack(L, nargs+LUA_MINSTACK, "too many arguments");
    ok = 1;
    for (n = start; nargs-- && ok; n++) {
      if (tvisstr(L->base+n)) {
	const char *p = strVdata(L->base+n);
	if (p[0] != '*')
	  lj_err_arg(L, n+1, LJ_ERR_INVOPT);
	if (p[1] == 'n')
	  ok = io_file_readnum(L, fp);
	else if ((p[1] & ~0x20) == 'L')
	  ok = io_file_readline(L, fp, (p[1] == 'l'));
	else if (p[1] == 'a')
	  io_file_readall(L, fp);
	else
	  lj_err_arg(L, n+1, LJ_ERR_INVFMT);
      } else if (tvisnumber(L->base+n)) {
	ok = io_file_readlen(L, fp, (MSize)lj_lib_checkint(L, n+1));
      } else {
	lj_err_arg(L, n+1, LJ_ERR_INVOPT);
      }
    }
  }
  if (ferror(fp))
    return luaL_fileresult(L, 0, NULL);
  if (!ok)
    setnilV(L->top-1);
  return n - start;
}
