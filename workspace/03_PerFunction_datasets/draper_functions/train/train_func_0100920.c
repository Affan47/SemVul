CHECKOBJ<Corpse>(lua_State* L, int narg, bool error)
{
    WorldObject* obj = CHECKOBJ<WorldObject>(L, narg, false);
    TEST_OBJ(Corpse, obj, error, ToCorpse);
}
