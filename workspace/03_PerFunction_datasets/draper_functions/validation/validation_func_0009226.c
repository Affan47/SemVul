syntaxCopyHelper(TypeQualified *t)
{

    idents.setDim(t->idents.dim);
    for (size_t i = 0; i < idents.dim; i++)
    {
        RootObject *id = t->idents[i];
        if (id->dyncast() == DYNCAST_DSYMBOL)
        {
            TemplateInstance *ti = (TemplateInstance *)id;

            ti = (TemplateInstance *)ti->syntaxCopy(NULL);
            id = ti;
        }
        idents[i] = id;
    }
}
