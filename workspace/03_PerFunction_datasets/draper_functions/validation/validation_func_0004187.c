t4_tx_end(t4_state_t *s)
{
    if (s->rx)
        return -1;
    if (s->tiff_file)
        close_tiff_input_file(s);
    free_buffers(s);
    return 0;
}
