propertyValuesSetEnum(p, pEVar, aOptions, pProp)
    HtmlComputedValuesCreator *p;
    unsigned char *pEVar;
    unsigned char *aOptions;
    CssProperty *pProp;
{
    int val = pProp->eType;
    unsigned char *pOpt;

    if (val == CSS_CONST_INHERIT) {
        unsigned char *pInherit = getInheritPointer(p, pEVar);
        if (pInherit) {
            *pEVar = *pInherit;
        }
        return 0;
    }

    for (pOpt = aOptions; *pOpt; pOpt++) {
        if (*pOpt == val) {
            *pEVar = (unsigned char)val;
            return 0;
        }
    }
    return 1;
}
