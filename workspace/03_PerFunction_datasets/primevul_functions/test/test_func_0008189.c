free_colour_buffer(void)
{
    if (--colseq_buf_allocs)
	return;

    DPUTS(!colseq_buf, "Freeing colour sequence buffer without alloc");

    free(colseq_buf);
    colseq_buf = NULL;
}
