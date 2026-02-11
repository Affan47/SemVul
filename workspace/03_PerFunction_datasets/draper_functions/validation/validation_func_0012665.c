jack_internal_initialize(jack_client_t* jack_client, const JSList* params)
    {
        if (master_manager) {
            jack_error("Master Manager already loaded");
            return 1;
        } else {
            jack_log("Loading Master Manager");
            master_manager = new Jack::JackNetMasterManager(jack_client, params);
            return (master_manager) ? 0 : 1;
        }
    }
