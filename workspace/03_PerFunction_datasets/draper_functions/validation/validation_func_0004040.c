gpe_pop(gpe_fifo_t ** base)
{
    buffered_output_pending--;
    if ((*base)->prev == (*base)) {
	(*base)->prev = (gpe_fifo_t *) 0;
	return 0;
    } else {
	gpe_fifo_t *save = *base;

	(*base)->next->prev = (*base)->prev;
	(*base) = (*base)->next;
	free(save);
	return 1;
    }
}
