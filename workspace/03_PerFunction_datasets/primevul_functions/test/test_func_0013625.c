static int forprep (lua_State *L, StkId ra) {
  TValue *pinit = s2v(ra);
  TValue *plimit = s2v(ra + 1);
  TValue *pstep = s2v(ra + 2);
  if (ttisinteger(pinit) && ttisinteger(pstep)) {
    lua_Integer init = ivalue(pinit);
    lua_Integer step = ivalue(pstep);
    lua_Integer limit;
    if (step == 0)
      luaG_runerror(L, "'for' step is zero");
    setivalue(s2v(ra + 3), init);
    if (forlimit(L, init, plimit, &limit, step))
      return 1;
    else {
      lua_Unsigned count;
      if (step > 0) {
        count = l_castS2U(limit) - l_castS2U(init);
        if (step != 1)
          count /= l_castS2U(step);
      }
      else {
        count = l_castS2U(init) - l_castS2U(limit);

        count /= l_castS2U(-(step + 1)) + 1u;
      }


      setivalue(plimit, l_castU2S(count));
    }
  }
  else {
    lua_Number init; lua_Number limit; lua_Number step;
    if (l_unlikely(!tonumber(plimit, &limit)))
      luaG_forerror(L, plimit, "limit");
    if (l_unlikely(!tonumber(pstep, &step)))
      luaG_forerror(L, pstep, "step");
    if (l_unlikely(!tonumber(pinit, &init)))
      luaG_forerror(L, pinit, "initial value");
    if (step == 0)
      luaG_runerror(L, "'for' step is zero");
    if (luai_numlt(0, step) ? luai_numlt(limit, init)
                            : luai_numlt(init, limit))
      return 1;
    else {

      setfltvalue(plimit, limit);
      setfltvalue(pstep, step);
      setfltvalue(s2v(ra), init);
      setfltvalue(s2v(ra + 3), init);
    }
  }
  return 0;
}
