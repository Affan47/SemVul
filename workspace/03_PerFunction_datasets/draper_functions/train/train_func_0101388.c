_mteEvent_fire_notify( struct mteEvent   *entry,
                       struct mteTrigger *trigger,
                       oid *suffix, size_t sfx_len )
{
    netsnmp_variable_list *var, *v2;
    extern const oid       snmptrap_oid[];
    extern const size_t    snmptrap_oid_len;
    netsnmp_session       *s;


    int strictOrdering = netsnmp_ds_get_boolean(
                             NETSNMP_DS_APPLICATION_ID,
                             NETSNMP_DS_AGENT_STRICT_DISMAN);

    var = (netsnmp_variable_list *)SNMP_MALLOC_TYPEDEF( netsnmp_variable_list );
    if (!var)
        return -1;


    memset(var, 0, sizeof(netsnmp_variable_list));
    snmp_set_var_objid( var, snmptrap_oid, snmptrap_oid_len );
    snmp_set_var_typed_value( var, ASN_OBJECT_ID,
                    (u_char *)entry->mteNotification,
                              entry->mteNotification_len*sizeof(oid));


    if (!strictOrdering) {
        DEBUGMSGTL(("disman:event:fire", "Adding event objects (first)\n"));
        if (strcmp(entry->mteNotifyOwner, "_snmpd") != 0)
            mteObjects_vblist( var, entry->mteNotifyOwner,
                                     entry->mteNotifyObjects,
                                     suffix, sfx_len );
    }

    DEBUGMSGTL(("disman:event:fire", "Adding trigger objects (general)\n"));
    mteObjects_vblist( var, trigger->mteTriggerOOwner,
                             trigger->mteTriggerObjects,
                             suffix, sfx_len );
    DEBUGMSGTL(("disman:event:fire", "Adding trigger objects (specific)\n"));
    mteObjects_vblist( var, trigger->mteTriggerXOwner,
                             trigger->mteTriggerXObjects,
                             suffix, sfx_len );

    if (strictOrdering) {
        DEBUGMSGTL(("disman:event:fire", "Adding event objects (last)\n"));
        if (strcmp(entry->mteNotifyOwner, "_snmpd") != 0)
            mteObjects_vblist( var, entry->mteNotifyOwner,
                                     entry->mteNotifyObjects,
                                     suffix, sfx_len );
    }


    v2 = var->next_variable;
    if (entry->session)
        s = entry->session;
    else
        s = trigger->session;
    netsnmp_query_get( v2, s );


    if (strcmp(entry->mteNotifyOwner, "_snmpd") == 0) {
        DEBUGMSGTL(("disman:event:fire", "Adding event objects (internal)\n"));
        if ( !strictOrdering ) {
            mteObjects_internal_vblist(var, entry->mteNotifyObjects, trigger, s);
        } else {
            for (v2 = var; v2 && v2->next_variable; v2=v2->next_variable)
                ;
            mteObjects_internal_vblist(v2, entry->mteNotifyObjects, trigger, s);
        }
    }


    send_v2trap( var );
    snmp_free_varbind( var );
    return 0;
}
