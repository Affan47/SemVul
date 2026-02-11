varchar(Var *var)
{
    if (!var || !(var->flags & VARSET))
        return NULL;
    if (!var->val.sval)
        valstr(&var->val);
    return var->val.sval->data;
}
