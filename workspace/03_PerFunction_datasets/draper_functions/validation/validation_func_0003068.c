implicitConvTo(Type *to)
{   MATCH m;


    if (equals(to))
        m = MATCHexact;
    else if (sym->basetype->implicitConvTo(to))
        m = MATCHconvert;
    else if (ty == to->ty && sym == ((TypeTypedef *)to)->sym)
    {
        m = constConv(to);
    }
    else
        m = MATCHnomatch;
    return m;
}
