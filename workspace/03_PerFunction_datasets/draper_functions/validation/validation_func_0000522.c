mainloop_del_fd(mainloop_io_t * client)
{
    if (client != NULL) {
        crm_trace("Removing client %s[%p]", client->name, client);
        if (client->source) {


            g_source_remove(client->source);
        }
    }
}
