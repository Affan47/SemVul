mgsl_reset_rx_dma_buffers( struct mgsl_struct *info )
{
	unsigned int i;

	for ( i = 0; i < info->rx_buffer_count; i++ ) {
		*((unsigned long *)&(info->rx_buffer_list[i].count)) = DMABUFFERSIZE;


	}

	info->current_rx_buffer = 0;

}
