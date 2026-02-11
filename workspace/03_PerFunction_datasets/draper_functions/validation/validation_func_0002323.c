lrmd_ipc_closed(qb_ipcs_connection_t * c)
{
    crm_client_t *client = crm_client_get(c);

    crm_trace("Connection %p", c);
    client_disconnect_cleanup(client->id);
#ifdef ENABLE_PCMK_REMOTE
    ipc_proxy_remove_provider(client);
#endif
    crm_client_destroy(client);
    return 0;
}
