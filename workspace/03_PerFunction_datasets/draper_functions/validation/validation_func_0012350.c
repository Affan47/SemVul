connectionTypes( const QByteArray& member, int& nargs )
{

    nargs = 0;
    int *types = 0;
    const char *s = member.constData();
    while (*s != '\0' && *s != '(') { ++s; }
    if ( *s == '\0' )
        return 0;
    ++s;
    const char *e = s;
    while (*e != ')') {
        ++e;
        if (*e == ')' || *e == ',')
            ++nargs;
    }

    types = (int *) qMalloc((nargs+1)*sizeof(int));
    types[nargs] = 0;
    for (int n = 0; n < nargs; ++n) {
        e = s;
        while (*s != ',' && *s != ')')
            ++s;
        QByteArray type(e, s-e);
        ++s;

        types[n] = typeFromName(type);
        if (!types[n]) {
            qWarning("QSignalIntercepter::connectionTypes: Cannot marshal arguments of type '%s'", type.data());
            qFree(types);
            return 0;
        }
    }
    return types;
}
