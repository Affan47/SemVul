routeDirective(MaState *state, cchar *key, cchar *value)
{
    HttpRoute   *route;
    char        *pattern, *name;
    int         not;

    state = maPushState(state);
    if (state->enabled) {
        if (!maTokenize(state, value, "%!%S", &not, &pattern)) {
            return MPR_ERR_BAD_SYNTAX;
        }
        if (strstr(pattern, "${")) {
            pattern = sreplace(pattern, "${inherit}", state->route->pattern);
        }
        name = (*pattern == '^') ? &pattern[1] : pattern;

        if ((route = httpLookupRoute(state->host, name)) != 0) {
            state->route = route;
        } else {
            state->route = httpCreateInheritedRoute(state->route);
            httpSetRoutePattern(state->route, pattern, not);
            httpSetRouteHost(state->route, state->host);
        }

        state->auth = state->route->auth;
    }
    return 0;
}
