_copy_pdu_vars(netsnmp_pdu *pdu,
               netsnmp_pdu *newpdu,
               int drop_err,
               int skip_count,
               int copy_count)
{
    netsnmp_variable_list *var;
#if TEMPORARILY_DISABLED
    int             copied;
#endif
    int             drop_idx;

    if (!newpdu)
        return NULL;

    if (drop_err)
        drop_idx = pdu->errindex - skip_count;
    else
        drop_idx = 0;

    var = pdu->variables;
    while (var && (skip_count-- > 0))
        var = var->next_variable;

#if TEMPORARILY_DISABLED
    copied = 0;
    if (pdu->flags & UCD_MSG_FLAG_FORCE_PDU_COPY)
        copied = 1;
#endif

    newpdu->variables = _copy_varlist(var, drop_idx, copy_count);
#if TEMPORARILY_DISABLED
    if (newpdu->variables)
        copied = 1;
#endif

#if ALSO_TEMPORARILY_DISABLED


    if ((drop_err && (ii < pdu->errindex))
#if TEMPORARILY_DISABLED


        || copied == 0
#endif
        ) {
        snmp_free_pdu(newpdu);
        return 0;
    }
#endif
    return newpdu;
}
