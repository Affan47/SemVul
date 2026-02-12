static void reds_agent_remove(RedsState *reds)
{


    reds_reset_vdp(reds);

    reds->vdagent = NULL;
    reds_update_mouse_mode(reds);
    if (reds_main_channel_connected(reds) &&
        !reds->main_channel->is_waiting_for_migrate_data()) {
        reds->main_channel->push_agent_disconnected();
    }
}
