_copy_varlist(netsnmp_variable_list * var,
              int errindex,
              int copy_count)
{
    netsnmp_variable_list *newhead, *newvar, *oldvar;
    int             ii = 0;

    newhead = NULL;
    oldvar = NULL;

    while (var && (copy_count-- > 0)) {


        if (++ii == errindex) {
            var = var->next_variable;
            continue;
        }


        newvar = (netsnmp_variable_list *)
            malloc(sizeof(netsnmp_variable_list));
        if (snmp_clone_var(var, newvar)) {
            if (newvar)
                free((char *) newvar);
            snmp_free_varbind(newhead);
            return NULL;
        }


        if (NULL == newhead)
            newhead = newvar;
        if (oldvar)
            oldvar->next_variable = newvar;
        oldvar = newvar;

        var = var->next_variable;
    }
    return newhead;
}
