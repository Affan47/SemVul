static int _query(netsnmp_variable_list *list,
                  int                    request,
                  netsnmp_session       *session) {

    netsnmp_pdu *pdu;
    netsnmp_pdu *response = NULL;
    netsnmp_variable_list *vb1, *vb2, *vtmp;
    int ret, count;

    DEBUGMSGTL(("iquery", "query on session %p\n", session));

    if (NULL == list) {
        snmp_log(LOG_ERR, "empty variable list in _query\n");
        return SNMP_ERR_GENERR;
    }

    pdu = snmp_pdu_create( request );
    if (NULL == pdu) {
        snmp_log(LOG_ERR, "could not allocate pdu\n");
        return SNMP_ERR_GENERR;
    }


    pdu->variables = snmp_clone_varbind( list );
    if (NULL == pdu->variables) {
        snmp_log(LOG_ERR, "could not clone variable list\n");
        snmp_free_pdu(pdu);
        return SNMP_ERR_GENERR;
    }

#ifndef NETSNMP_NO_WRITE_SUPPORT
retry:
#endif
    if ( session )
        ret = snmp_synch_response(            session, pdu, &response );
    else if (_def_query_session)
        ret = snmp_synch_response( _def_query_session, pdu, &response );
    else {

        snmp_free_pdu(pdu);
        return SNMP_ERR_GENERR;
    }
    DEBUGMSGTL(("iquery", "query returned %d\n", ret));


    if ( ret == SNMP_ERR_NOERROR ) {
        if ( response->errstat != SNMP_ERR_NOERROR ) {
            DEBUGMSGT(("iquery", "Error in packet: %s\n",
                       snmp_errstring(response->errstat)));


            ret = response->errstat;
            if (response->errindex != 0) {
                DEBUGMSGT(("iquery:result", "Failed object:\n"));
                for (count = 1, vtmp = response->variables;
                     vtmp && count != response->errindex;
                     vtmp = vtmp->next_variable, count++)
                    ;
                if (vtmp)
                    DEBUGMSGVAR(("iquery:result", vtmp));
                DEBUGMSG(("iquery:result", "\n"));
            }
#ifndef NETSNMP_NO_WRITE_SUPPORT
            if (request != SNMP_MSG_SET &&
                response->errindex != 0) {
                DEBUGMSGTL(("iquery", "retrying query (%d, %ld)\n", ret, response->errindex));
                pdu = snmp_fix_pdu( response, request );
                snmp_free_pdu( response );
                response = NULL;
                if ( pdu != NULL )
                    goto retry;
            }
#endif
        } else {
            for (vb1 = response->variables, vb2 = list;
                 vb1;
                 vb1 = vb1->next_variable,  vb2 = vb2->next_variable) {
                DEBUGMSGVAR(("iquery:result", vb1));
                DEBUGMSG(("iquery:results", "\n"));
                if ( !vb2 ) {
                    ret = SNMP_ERR_GENERR;
                    break;
                }
                vtmp = vb2->next_variable;
                snmp_free_var_internals( vb2 );
                snmp_clone_var( vb1, vb2 );
                vb2->next_variable = vtmp;
            }
        }
    } else {

        ret = -ret;
    }
    snmp_free_pdu( response );
    return ret;
}
