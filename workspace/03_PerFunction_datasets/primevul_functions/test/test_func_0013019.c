int reds_get_free_channel_id(RedsState *reds, uint32_t type)
{


    bool used_ids[256];

    unsigned n;


    memset(used_ids, 0, sizeof(used_ids));
    for (const auto channel: reds->channels) {
        if (channel->type() == type && channel->id() < SPICE_N_ELEMENTS(used_ids)) {
            used_ids[channel->id()] = true;
        }
    }


    for (n = 0; n < SPICE_N_ELEMENTS(used_ids); ++n) {
        if (!used_ids[n]) {
            return n;
        }
    }
    return -1;
}
