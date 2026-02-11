netsnmp_check_vb_type(const netsnmp_variable_list *var, int type )
{
    register int rc = SNMP_ERR_NOERROR;

    if (NULL == var)
        return SNMP_ERR_GENERR;

    if (var->type != type) {
        rc = SNMP_ERR_WRONGTYPE;
    }

    return rc;
}
