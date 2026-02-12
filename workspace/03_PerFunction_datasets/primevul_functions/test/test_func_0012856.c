SPICE_GNUC_VISIBLE void spice_server_destroy(SpiceServer *reds)
{


    pthread_mutex_lock(&global_reds_lock);
    servers = g_list_remove(servers, reds);
    pthread_mutex_unlock(&global_reds_lock);

    for (auto qxl: reds->qxl_instances) {
        red_qxl_destroy(qxl);
    }

    if (reds->inputs_channel) {
        reds->inputs_channel->destroy();
    }


    if (reds->main_channel) {
        reds->main_channel->destroy();
    }
    red_timer_remove(reds->mig_timer);

    if (reds->ctx) {
        SSL_CTX_free(reds->ctx);
    }

    reds->main_dispatcher.reset();
    reds_cleanup_net(reds);
    reds->agent_dev.reset();


    reds->char_devices.clear();

    spice_buffer_free(&reds->client_monitors_config);
    red_record_unref(reds->record);
    reds_cleanup(reds);
#ifdef RED_STATISTICS
    stat_file_free(reds->stat_file);
#endif

    reds_config_free(reds->config);
    delete reds;
}
