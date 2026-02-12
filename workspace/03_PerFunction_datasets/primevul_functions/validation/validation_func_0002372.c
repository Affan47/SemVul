void CLua::init_lua()
{
    if (_state)
        return;

#ifdef NO_CUSTOM_ALLOCATOR


# if defined(USE_TILE_WEB) || defined(DGAMELAUNCH)
#   warning Detected 64-bit Luajit, disabling CLua memory throttling.
# endif
    _state = luaL_newstate();
#else

    _state = managed_vm? lua_newstate(_clua_allocator, this) : luaL_newstate();
#endif
    if (!_state)
        end(1, false, "Unable to create Lua state.");

    lua_stack_cleaner clean(_state);

    lua_atpanic(_state, _clua_panic);

#ifdef CLUA_UNRESTRICTED_LIBS


    luaL_openlibs(_state);
#else


    const vector<pair<string, lua_CFunction>> lua_core_libs =
    {
        {"", luaopen_base},
        {LUA_TABLIBNAME, luaopen_table},
        {LUA_STRLIBNAME, luaopen_string},
        {LUA_MATHLIBNAME, luaopen_math},
    };

    for (auto l : lua_core_libs)
    {
        lua_pushcfunction(_state, l.second);
        lua_pushstring(_state, l.first.c_str());
        lua_call(_state, 1, 0);
    }
#endif

    lua_pushboolean(_state, managed_vm);
    setregistry("lua_vm_is_managed");

    lua_pushlightuserdata(_state, this);
    setregistry("__clua");
}
