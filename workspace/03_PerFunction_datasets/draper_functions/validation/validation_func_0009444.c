getMaxMinValue(Loc loc, Identifier *id)
{

    bool first = true;

    Expression **pval = (id == Id::max) ? &maxval : &minval;

    if (*pval)
        return *pval;

    if (scope)
        semantic(scope);
    if (errors)
        goto Lerrors;
    if (semanticRun == PASSinit || !members)
    {
        error("is forward referenced looking for .%s", id->toChars());
        goto Lerrors;
    }
    if (!(memtype && memtype->isintegral()))
    {
        error(loc, "has no .%s property because base type %s is not an integral type",
                id->toChars(),
                memtype ? memtype->toChars() : "");
        goto Lerrors;
    }

    for (size_t i = 0; i < members->dim; i++)
    {
        EnumMember *em = (*members)[i]->isEnumMember();
        if (!em)
            continue;
        if (em->errors)
            goto Lerrors;

        Expression *e = em->value;
        if (first)
        {
            *pval = e;
            first = false;
        }
        else
        {


            Expression *ec = new CmpExp(id == Id::max ? TOKgt : TOKlt, em->loc, e, *pval);
            ec = ec->semantic(em->scope);
            ec = ec->ctfeInterpret();
            if (ec->toInteger())
                *pval = e;
        }
    }
    return *pval;

Lerrors:
    *pval = new ErrorExp();
    return *pval;
}
