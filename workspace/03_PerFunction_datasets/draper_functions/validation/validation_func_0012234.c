notification_log_config_handler(netsnmp_mib_handler *handler,
                                netsnmp_handler_registration *reginfo,
                                netsnmp_agent_request_info *reqinfo,
                                netsnmp_request_info *requests)
{


#ifndef NETSNMP_NO_WRITE_SUPPORT
    if (reqinfo->mode == MODE_SET_COMMIT)
        check_log_size(0, NULL);
#endif
    return SNMP_ERR_NOERROR;
}
