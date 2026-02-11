semantic(Scope *sc)
{
#if LOGSEMANTIC
    printf("PtrExp::semantic('%s')\n", toChars());
#endif
    if (!type)
    {
        Expression *e = op_overload(sc);
        if (e)
            return e;
        Type *tb = e1->type->toBasetype();
        switch (tb->ty)
        {
            case Tpointer:
                type = ((TypePointer *)tb)->next;
                break;

            case Tsarray:
            case Tarray:
                deprecation("using * on an array is deprecated; use *(%s).ptr instead", e1->toChars());
                type = ((TypeArray *)tb)->next;
                e1 = e1->castTo(sc, type->pointerTo());
                break;

            default:
                error("can only * a pointer, not a '%s'", e1->type->toChars());
            case Terror:
                return new ErrorExp();
        }
        if (!rvalue())
            return new ErrorExp();
    }
    return this;
}
