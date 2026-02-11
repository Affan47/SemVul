Scm_ModuleNameToPath(ScmSymbol *name)
{
    const ScmStringBody *b = SCM_STRING_BODY(SCM_SYMBOL_NAME(name));
    char *buf = SCM_NEW_ATOMIC2(char *, SCM_STRING_BODY_SIZE(b)+1);
    char *p = buf, *e = buf + SCM_STRING_BODY_SIZE(b);
    memcpy(buf, SCM_STRING_BODY_START(b), SCM_STRING_BODY_SIZE(b));
    while (p < e) {
        int n = SCM_CHAR_NFOLLOWS(*p);
        if (*p == '.') *p++ = '/';
        else p += n+1;
    }
    *e = '\0';
    return Scm_MakeString(buf, SCM_STRING_BODY_SIZE(b),
                          SCM_STRING_BODY_LENGTH(b), 0);
}
