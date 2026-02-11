tolua_bnd_cast (lua_State* L)
{


	void* v;
	const char* s;
	if (lua_islightuserdata(L, 1)) {
		v = tolua_touserdata(L, 1, NULL);
	} else {
		v = tolua_tousertype(L, 1, 0);
	};

	s = tolua_tostring(L,2,NULL);
	if (v && s)
	 tolua_pushusertype(L,v,s);
	else
	 lua_pushnil(L);
	return 1;
}
