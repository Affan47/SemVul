closeDirective(MaState *state, cchar *key, cchar *value)
{


    if (state->route != state->prev->route) {
        httpFinalizeRoute(state->route);
    }
    maPopState(state);
    return 0;
}
