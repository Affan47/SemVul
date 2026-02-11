proctable_post_config(server_rec * main_server, apr_pool_t * configpool)
{
    size_t shmem_size = sizeof(fcgid_share);
    fcgid_procnode *ptmpnode = NULL;
    int i;
    apr_status_t rv;
    fcgid_server_conf *sconf = ap_get_module_config(main_server->module_config,
                                                    &fcgid_module);


    apr_shm_remove(sconf->shmname_path, main_server->process->pconf);


    if ((rv = apr_shm_create(&g_sharemem, shmem_size, sconf->shmname_path,
                             main_server->process->pconf)) != APR_SUCCESS)
    {
        ap_log_error(APLOG_MARK, APLOG_EMERG, rv, main_server,
                     "mod_fcgid: Can't create shared memory for size %" APR_SIZE_T_FMT " bytes",
                     shmem_size);
        exit(1);
    }
    _global_memory = apr_shm_baseaddr_get(g_sharemem);


    rv = fcgid_mutex_create(&g_sharelock, &g_sharelock_name,
                            g_sharelock_mutex_type,
                            main_server->process->pconf, main_server);
    if (rv != APR_SUCCESS) {
        exit(1);
    }

    memset(_global_memory, 0, shmem_size);
    g_proc_array = _global_memory->procnode_array;
    g_global_share = &_global_memory->global;

    g_global_share->must_exit = 0;


    g_idle_list_header = g_proc_array;
    g_busy_list_header = g_idle_list_header + 1;
    g_error_list_header = g_busy_list_header + 1;
    g_free_list_header = g_error_list_header + 1;
    ptmpnode = g_free_list_header;
    for (i = 0; i < FCGID_MAX_APPLICATION; i++) {
        ptmpnode->next_index = ptmpnode - g_proc_array + 1;
        ptmpnode++;
    }

    return APR_SUCCESS;
}
