int netsnmp_query_walk(netsnmp_variable_list *list,
                       netsnmp_session       *session) {


    netsnmp_variable_list *vb = snmp_clone_varbind( list );
    netsnmp_variable_list *res_list = NULL;
    netsnmp_variable_list *res_last = NULL;
    int ret;


    ret = _query( vb, SNMP_MSG_GETNEXT, session );
    while ( ret == SNMP_ERR_NOERROR &&
        snmp_oidtree_compare( list->name, list->name_length,
                                vb->name,   vb->name_length ) == 0) {

	if (vb->type == SNMP_ENDOFMIBVIEW ||
	    vb->type == SNMP_NOSUCHOBJECT ||
	    vb->type == SNMP_NOSUCHINSTANCE)
	    break;


        if ( res_last ) {
            res_last->next_variable = snmp_clone_varbind( vb );
            res_last = res_last->next_variable;
        } else {
            res_list = snmp_clone_varbind( vb );
            res_last = res_list;
        }
        ret = _query( vb, SNMP_MSG_GETNEXT, session );
    }


    if ( res_list ) {
        snmp_clone_var( res_list, list );
        list->next_variable = res_list->next_variable;
        res_list->next_variable = NULL;
        snmp_free_varbind( res_list );
    }
    snmp_free_varbind( vb );
    return ret;
}
