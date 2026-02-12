multi_client_disconnect_setenv(struct multi_instance *mi)
{

    setenv_trusted(mi->context.c2.es, get_link_socket_info(&mi->context));


    setenv_stats(&mi->context);


    setenv_long_long(mi->context.c2.es, "time_duration", now - mi->created);
}
