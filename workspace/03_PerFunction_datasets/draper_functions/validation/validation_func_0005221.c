checkFrameAccess(Loc loc, Scope *sc, AggregateDeclaration *ad)
{
    if (!ad->isNested())
        return;

    Dsymbol *s = sc->func;
    if (s)
    {
        Dsymbol *sparent = ad->toParent2();


        while (s)
        {
            if (s == sparent)
            {

                for (size_t i = 0; i < ad->fields.dim; i++)
                {   VarDeclaration *vd = ad->fields[i]->isVarDeclaration();
                    if (vd)
                        if (AggregateDeclaration *ad2 = isAggregate(vd->type))
                            if (ad2->isStructDeclaration())
                                checkFrameAccess(loc, sc, ad2);
                }
                return;
            }

            if (FuncDeclaration *fd = s->isFuncDeclaration())
            {
                if (!fd->isThis() && !fd->isNested())
                    break;
            }
            if (AggregateDeclaration *ad2 = s->isAggregateDeclaration())
            {
                if (ad2->storage_class & STCstatic)
                    break;
            }
            s = s->toParent2();
        }
    }
    error(loc, "cannot access frame pointer of %s", ad->toPrettyChars());
}
