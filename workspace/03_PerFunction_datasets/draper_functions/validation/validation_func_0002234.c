ImposeHint () {
    uint64_t twist = peer_channel_id_;

    twist &= file().peak(0).toUInt();

    bin_t my_pick = binmap_t::find_complement(ack_in_, file().ack_out(), twist);

    my_pick.to_twisted(twist);
    while (my_pick.base_length()>max(1,(int)cwnd_))
        my_pick = my_pick.left();

    return my_pick.twisted(twist);
}
