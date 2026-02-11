t38_terminal_set_config(t38_terminal_state_t *s, int without_pacing)
{
    if (without_pacing)
    {


        t38_set_redundancy_control(&s->t38_fe.t38, T38_PACKET_CATEGORY_INDICATOR, 0);
        t38_set_redundancy_control(&s->t38_fe.t38, T38_PACKET_CATEGORY_CONTROL_DATA, 1);
        t38_set_redundancy_control(&s->t38_fe.t38, T38_PACKET_CATEGORY_CONTROL_DATA_END, 1);
        t38_set_redundancy_control(&s->t38_fe.t38, T38_PACKET_CATEGORY_IMAGE_DATA, 1);
        t38_set_redundancy_control(&s->t38_fe.t38, T38_PACKET_CATEGORY_IMAGE_DATA_END, 1);
        s->t38_fe.ms_per_tx_chunk = 0;
    }
    else
    {

        t38_set_redundancy_control(&s->t38_fe.t38, T38_PACKET_CATEGORY_INDICATOR, INDICATOR_TX_COUNT);
        t38_set_redundancy_control(&s->t38_fe.t38, T38_PACKET_CATEGORY_CONTROL_DATA, DATA_TX_COUNT);
        t38_set_redundancy_control(&s->t38_fe.t38, T38_PACKET_CATEGORY_CONTROL_DATA_END, DATA_END_TX_COUNT);
        t38_set_redundancy_control(&s->t38_fe.t38, T38_PACKET_CATEGORY_IMAGE_DATA, DATA_TX_COUNT);
        t38_set_redundancy_control(&s->t38_fe.t38, T38_PACKET_CATEGORY_IMAGE_DATA_END, DATA_END_TX_COUNT);
        s->t38_fe.ms_per_tx_chunk = MS_PER_TX_CHUNK;
    }
    set_octets_per_data_packet(s, 300);
}
