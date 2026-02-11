Scm_LastPair(ScmObj l)
{
    ScmObj cp;

    if (!SCM_PAIRP(l)) Scm_Error("pair required: %S", l);
    SCM_FOR_EACH(cp, l) {
	ScmObj cdr = SCM_CDR(cp);
	if (!SCM_PAIRP(cdr)) return cp;
    }
    return SCM_UNDEFINED;
}
