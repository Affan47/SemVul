Scm_ImportModule(ScmModule *module,
                        ScmObj imported,
                        ScmObj prefix,
                        u_long flags)
{
    ScmModule *imp = NULL;
    ScmObj p;
    if (SCM_MODULEP(imported)) {
        imp = SCM_MODULE(imported);
    } else if (SCM_SYMBOLP(imported)) {
        imp = Scm_FindModule(SCM_SYMBOL(imported), 0);
    } else if (SCM_IDENTIFIERP(imported)) {
        imp = Scm_FindModule(SCM_IDENTIFIER(imported)->name, 0);
    } else {
        Scm_Error("module name or module required, but got %S", imported);
    }

    if (SCM_SYMBOLP(prefix)) {
        imp = SCM_MODULE(Scm__MakeWrapperModule(imp, prefix));
    }


    p = Scm_Cons(SCM_OBJ(imp), SCM_NIL);


    (void)SCM_INTERNAL_MUTEX_LOCK(modules.mutex);
    {
        ScmObj ms, prev = p;
        SCM_SET_CDR(p, module->imported);

        SCM_FOR_EACH(ms, SCM_CDR(p)) {
            ScmModule *m = SCM_MODULE(SCM_CAR(ms));
            ScmObj b0 = SCM_MODULEP(m->origin)? m->origin : SCM_OBJ(m);
            ScmObj b1 = SCM_MODULEP(imp->origin)? imp->origin : SCM_OBJ(imp);
            if (!SCM_EQ(b0, b1)) {
                prev = ms;
                continue;
            }
            SCM_SET_CDR(prev, SCM_CDR(ms));
            break;
        }
        module->imported = p;
    }
    (void)SCM_INTERNAL_MUTEX_UNLOCK(modules.mutex);

    return module->imported;
}
