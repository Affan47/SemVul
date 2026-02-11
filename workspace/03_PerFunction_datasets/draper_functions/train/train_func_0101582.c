Scm_ExportSymbols(ScmModule *module, ScmObj list)
{
    ScmObj lp, syms, badsym = SCM_FALSE;
    int error = FALSE;
    ScmSymbol *s;
    ScmDictEntry *e;
    ScmGloc *g;


    (void)SCM_INTERNAL_MUTEX_LOCK(modules.mutex);
    syms = module->exported;
    SCM_FOR_EACH(lp, list) {
        if (!SCM_SYMBOLP(SCM_CAR(lp))) {
            error = TRUE;
            badsym = SCM_CAR(lp);
            break;
        }
        s = SCM_SYMBOL(SCM_CAR(lp));
        e = Scm_HashCoreSearch(SCM_HASH_TABLE_CORE(module->table),
                               (intptr_t)s, SCM_DICT_CREATE);
        if (e->value) {
            g = SCM_GLOC(e->value);
            if (!g->exported) {
                syms = Scm_Cons(SCM_OBJ(s), syms);
                g->exported = TRUE;
            }
        } else {
            g = SCM_GLOC(Scm_MakeGloc(s, module));
            g->exported = TRUE;
            (void)SCM_DICT_SET_VALUE(e, SCM_OBJ(g));
            syms = Scm_Cons(SCM_OBJ(s), syms);
        }
    }
    if (!error) module->exported = syms;
    (void)SCM_INTERNAL_MUTEX_UNLOCK(modules.mutex);
    if (error) Scm_Error("symbol required, but got %S", badsym);
    return syms;
}
