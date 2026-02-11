adjust_varargs (StkId first_extra_arg)
{
  Object arg;
  Object *firstelem = stack+first_extra_arg;
  int nvararg = top-firstelem;
  int i;
  if (nvararg < 0) nvararg = 0;
  avalue(&arg)  = lua_createarray(nvararg+1);
  tag(&arg) = LUA_T_ARRAY;
  for (i=0; i<nvararg; i++) {
    Object index;
    tag(&index) = LUA_T_NUMBER;
    nvalue(&index) = i+1;
    *(lua_hashdefine(avalue(&arg), &index)) = *(firstelem+i);
  }
   {
    Object index, extra;
    tag(&index) = LUA_T_STRING;
    tsvalue(&index) = lua_createstring("n");
    tag(&extra) = LUA_T_NUMBER;
    nvalue(&extra) = nvararg;
    *(lua_hashdefine(avalue(&arg), &index)) = extra;
  }
  adjust_top(first_extra_arg);
  *top = arg; incr_top;
}
