agentx_check_packet(u_char * packet, size_t packet_len)
{

    if (packet_len < 20)
        return 0;

    return agentx_parse_int(packet + 16,
                            *(packet +
                              2) & AGENTX_FLAGS_NETWORK_BYTE_ORDER) + 20;
}
