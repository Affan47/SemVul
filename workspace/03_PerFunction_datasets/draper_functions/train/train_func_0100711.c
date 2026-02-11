repl_prompt_cc(ScmObj result, void **data)
{
    ScmObj *closure = (ScmObj*)data;
    ScmObj reader = closure[0];

    if (SCM_PROCEDUREP(reader)) {
        Scm_VMPushCC(repl_read_cc, data, 4);
        return Scm_VMApply0(reader);
    } else {
        ScmObj exp = Scm_Read(SCM_OBJ(SCM_CURIN));
        return repl_read_cc(exp, data);
    }
}
