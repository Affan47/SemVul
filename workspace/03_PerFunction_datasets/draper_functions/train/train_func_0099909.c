crmd_ipc_dispatch(qb_ipcs_connection_t * c, void *data, size_t size)
{
    uint32_t id = 0;
    uint32_t flags = 0;
    crm_client_t *client = crm_client_get(c);

    xmlNode *msg = crm_ipcs_recv(client, data, size, &id, &flags);

    crm_trace("Invoked: %s", crm_client_name(client));

    if (flags & crm_ipc_client_response) {
        crm_ipcs_send_ack(client, id, "ack", __FUNCTION__, __LINE__);
    }

    if (msg == NULL) {
        return 0;
    }
#if ENABLE_ACL
    determine_request_user(client->user, msg, F_CRM_USER);
#endif

    crm_trace("Processing msg from %s", crm_client_name(client));
    crm_log_xml_trace(msg, "CRMd[inbound]");

    crm_xml_add(msg, F_CRM_SYS_FROM, client->id);
    if (crmd_authorize_message(msg, client, NULL)) {
        route_message(C_IPC_MESSAGE, msg);
    }

    trigger_fsa(fsa_source);
    free_xml(msg);
    return 0;
}
