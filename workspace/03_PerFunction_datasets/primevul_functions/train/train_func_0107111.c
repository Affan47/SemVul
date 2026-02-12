void sdhci_common_unrealize(SDHCIState *s)
{


    g_free(s->fifo_buffer);
    s->fifo_buffer = NULL;
}
