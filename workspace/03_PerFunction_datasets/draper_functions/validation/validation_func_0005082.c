jack_controller_destroy(
        void * context)
{
    if (controller_ptr->started)
    {
        while (!jack_controller_stop_server(controller_ptr, NULL))
        {
            jack_info("jack server failed to stop, retrying in 3 seconds...");
            usleep(3000000);
        }
    }

    jack_controller_remove_slave_drivers(controller_ptr);
    jack_params_destroy(controller_ptr->params);
    jackctl_server_destroy(controller_ptr->server);
    pthread_mutex_destroy(&controller_ptr->lock);
    free(controller_ptr);
}
