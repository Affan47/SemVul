void packet_init(  struct gps_packet_t *lexer)
{
    lexer->char_counter = 0;
    lexer->retry_counter = 0;
#ifdef PASSTHROUGH_ENABLE
    lexer->json_depth = 0;
#endif
#ifdef TIMING_ENABLE
    lexer->start_time = 0.0;
#endif
    packet_reset(lexer);
}
