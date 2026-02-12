bool Parser::FncDeclAllowedWithoutContext(ushort flags)
{


    return !IsStrictMode() && !(flags & fFncAsync);
}
