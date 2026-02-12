void CLua::pushglobal(const string &name)
{
    vector<string> pieces = split_string(".", name);
    lua_State *ls(state());

    if (pieces.empty())
        lua_pushnil(ls);

    for (unsigned i = 0, size = pieces.size(); i < size; ++i)
    {
        if (!i)
            lua_getglobal(ls, pieces[i].c_str());
        else
        {
            if (lua_istable(ls, -1))
            {
                lua_pushstring(ls, pieces[i].c_str());
                lua_gettable(ls, -2);

                lua_insert(ls, -2);

                lua_pop(ls, 1);
            }
            else
            {

                lua_pop(ls, 1);
                lua_pushnil(ls);
                break;
            }
        }
    }
}
