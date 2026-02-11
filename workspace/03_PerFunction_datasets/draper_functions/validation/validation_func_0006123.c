smsboxc_run(void *arg)
{
    int fd;

    gwlist_add_producer(flow_threads);
    gwthread_wakeup(MAIN_THREAD_ID);

    fd = make_server_socket(smsbox_port, smsbox_interface ? octstr_get_cstr(smsbox_interface) : NULL);

    if (fd < 0) {
        panic(0, "Could not open smsbox port %ld", smsbox_port);
    }


    wait_for_connections(fd, run_smsbox, incoming_sms, smsbox_port_ssl);

    gwlist_remove_producer(smsbox_list);


    gwlist_remove_producer(outgoing_sms);


    while(gwlist_wait_until_nonempty(smsbox_list) == 1)
        gwthread_sleep(1.0);


    close(fd);

    gwthread_wakeup(sms_dequeue_thread);
    gwthread_join(sms_dequeue_thread);

    gwlist_destroy(smsbox_list, NULL);
    smsbox_list = NULL;
    gw_rwlock_destroy(smsbox_list_rwlock);
    smsbox_list_rwlock = NULL;


    dict_destroy(smsbox_by_id);
    smsbox_by_id = NULL;
    dict_destroy(smsbox_by_smsc);
    smsbox_by_smsc = NULL;
    dict_destroy(smsbox_by_receiver);
    smsbox_by_receiver = NULL;
    dict_destroy(smsbox_by_smsc_receiver);
    smsbox_by_smsc_receiver = NULL;

    gwlist_remove_producer(flow_threads);
}
