lapm_tx_frame(lapm_state_t *s, uint8_t *frame, int len)
{
    if ((s->debug & LAPM_DEBUG_LAPM_DUMP))
        lapm_dump(s, frame, len, s->debug & LAPM_DEBUG_LAPM_RAW, TRUE);

    hdlc_tx_frame(&s->hdlc_tx, frame, len);
    return 0;
}
