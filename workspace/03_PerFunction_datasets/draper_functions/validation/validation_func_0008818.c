toDocBuffer(OutBuffer *buf, Scope *sc)
{
    if (ident)
    {
        buf->printf("%s %s", kind(), toChars());
        if (memtype)
        {
            buf->writestring(": $(DDOC_ENUM_BASETYPE ");
            HdrGenState *hgs = NULL;
            memtype->toCBuffer(buf, NULL, hgs);
            buf->writestring(")");
        }
        buf->writestring(";\n");
    }
}
