void net_check_clients(void)
{
    NetClientState *nc;
    int i;

    net_hub_check_clients();

    QTAILQ_FOREACH(nc, &net_clients, next) {
        if (!nc->peer) {
            warn_report("%s %s has no peer",
                        nc->info->type == NET_CLIENT_DRIVER_NIC
                        ? "nic" : "netdev",
                        nc->name);
        }
    }


    for (i = 0; i < MAX_NICS; i++) {
        NICInfo *nd = &nd_table[i];
        if (nd->used && !nd->instantiated) {
            warn_report("requested NIC (%s, model %s) "
                        "was not created (not supported by this machine?)",
                        nd->name ? nd->name : "anonymous",
                        nd->model ? nd->model : "unspecified");
        }
    }
}
