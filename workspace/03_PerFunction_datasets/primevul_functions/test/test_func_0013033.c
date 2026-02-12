static void migrate_timeout(RedsState *reds)
{
    spice_debug("trace");
    spice_assert(reds->mig_wait_connect || reds->mig_wait_disconnect);
    if (reds->mig_wait_connect) {

        reds->main_channel->migrate_cancel_wait();

        reds_mig_target_client_disconnect_all(reds);
        reds_mig_cleanup(reds);
    } else {
        reds_mig_disconnect(reds);
    }
}
