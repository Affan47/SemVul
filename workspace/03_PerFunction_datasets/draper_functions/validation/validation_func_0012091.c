OnConfigLoad(bool reload)
{
    EVENT_BEGIN(ServerEventBindings, WORLD_EVENT_ON_CONFIG_LOAD, return);
    Push(L, reload);
    EVENT_EXECUTE(0);
    ENDCALL();
}
