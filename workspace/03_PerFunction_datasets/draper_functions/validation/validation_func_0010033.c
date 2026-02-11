port_remove(int port)
{
    Octstr *key;
    struct port *p;
    List *l;
    HTTPClient *client;

    key = port_key(port);
    mutex_lock(port_mutex);
    p = dict_remove(port_collection, key);
    mutex_unlock(port_mutex);
    octstr_destroy(key);

    if (p == NULL) {
        error(0, "HTTP: Could not find port (%d) in port_collection.", port);
        return;
    }

    gwlist_remove_producer(p->clients_with_requests);
    while (counter_value(p->active_consumers) > 0)
       gwthread_sleep(0.1);
    gwlist_destroy(p->clients_with_requests, client_destroy);
    counter_destroy(p->active_consumers);
    gw_free(p);


    gwlist_lock(active_connections);
    l = gwlist_search_all(active_connections, &port, port_match);
    while(l != NULL && (client = gwlist_extract_first(l)) != NULL)
        conn_unregister(client->conn);
    gwlist_unlock(active_connections);
    gwlist_destroy(l, NULL);
    while((client = gwlist_search(active_connections, &port, port_match)) != NULL)
        client_destroy(client);
}
