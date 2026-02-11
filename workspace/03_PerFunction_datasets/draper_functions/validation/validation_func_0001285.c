snmpNotifyFilterTable_container_init(netsnmp_container **container_ptr_ptr)
{
    DEBUGMSGTL(("verbose:snmpNotifyFilterTable:snmpNotifyFilterTable_container_init", "called\n"));

    if (NULL == container_ptr_ptr) {
        snmp_log(LOG_ERR,
                 "bad container param to snmpNotifyFilterTable_container_init\n");
        return;
    }


    *container_ptr_ptr = NULL;

}
