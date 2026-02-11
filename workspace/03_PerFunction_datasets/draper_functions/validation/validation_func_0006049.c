buildArrayIdent(OutBuffer *buf, Expressions *arguments)
{
    Type *tb = type->toBasetype();
    if (tb->ty == Tarray || tb->ty == Tsarray)
    {
        e1->buildArrayIdent(buf, arguments);
    }
    else
        Expression::buildArrayIdent(buf, arguments);
}
