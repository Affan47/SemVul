callCpCtor(Scope *sc, Expression *e)
{
    Type *tv = e->type->baseElemOf();
    if (tv->ty == Tstruct)
    {
        StructDeclaration *sd = ((TypeStruct *)tv)->sym;
        if (sd->cpctor)
        {


            Identifier *idtmp = Lexer::uniqueId("__cpcttmp");
            VarDeclaration *tmp = new VarDeclaration(e->loc, e->type, idtmp, new ExpInitializer(e->loc, e));
            tmp->storage_class |= STCctfe;
            tmp->noscope = 1;
            tmp->semantic(sc);
            Expression *de = new DeclarationExp(e->loc, tmp);
            Expression *ve = new VarExp(e->loc, tmp);
            de->type = Type::tvoid;
            ve->type = e->type;
            e = Expression::combine(de, ve);
        }
    }
    return e;
}
