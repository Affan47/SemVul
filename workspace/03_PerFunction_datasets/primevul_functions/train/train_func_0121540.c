void test_overflow(SpiceMarshaller *m)
{
    SpiceMsgChannels *msg;
    uint8_t *data, *out;
    size_t len;
    int to_free = 0;
    spice_parse_channel_func_t func;
    unsigned int max_message_type, n;
    message_destructor_t free_output;

    msg = (SpiceMsgChannels *) malloc(sizeof(SpiceMsgChannels) +
          NUM_CHANNELS * sizeof(uint16_t));
    g_assert_nonnull(msg);


    msg->num_of_channels = NUM_CHANNELS;
    for (n = 0; n < NUM_CHANNELS; ++n) {
        msg->channels[n] = n + 1;
    }
    spice_marshall_msg_main_channels_list(m, msg);


    data = spice_marshaller_linearize(m, 0, &len, &to_free);
    g_assert_nonnull(data);

    printf("output len %lu\n", (unsigned long) len);


    *((uint32_t *) data) = 0x80000002u;


    func = spice_get_server_channel_parser(SPICE_CHANNEL_MAIN, &max_message_type);
    g_assert_nonnull(func);
    out = func(data, data+len, SPICE_MSG_MAIN_CHANNELS_LIST, 0, &len, &free_output);
    g_assert_null(out);


    if (to_free) {
        free(data);
    }
    if (out) {
        free_output(out);
    }
    free(msg);
}
