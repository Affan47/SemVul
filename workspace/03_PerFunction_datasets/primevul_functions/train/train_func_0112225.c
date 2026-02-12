snmp_clone_var(netsnmp_variable_list * var, netsnmp_variable_list * newvar)
{
    if (!newvar || !var)
        return 1;

    memmove(newvar, var, sizeof(netsnmp_variable_list));
    newvar->next_variable = NULL;
    newvar->name = NULL;
    newvar->val.string = NULL;
    newvar->data = NULL;
    newvar->dataFreeHook = NULL;
    newvar->index = 0;


    if (snmp_set_var_objid(newvar, var->name, var->name_length))
        return 1;


    if (var->val.string) {
        if (var->val.string != &var->buf[0]) {
            if (var->val_len <= sizeof(var->buf))
                newvar->val.string = newvar->buf;
            else {
                newvar->val.string = (u_char *) malloc(var->val_len);
                if (!newvar->val.string)
                    return 1;
            }
            memmove(newvar->val.string, var->val.string, var->val_len);
        } else {
            newvar->val.string = newvar->buf;


        }
    } else {
        newvar->val.string = NULL;
        newvar->val_len = 0;
    }

    return 0;
}
