mxser_board_remove(struct mxser_board *brd)
{
	unsigned int i;

	for (i = 0; i < brd->info->nports; i++) {
		tty_unregister_device(mxvar_sdriver, brd->idx + i);
		tty_port_destroy(&brd->ports[i].port);
	}
	free_irq(brd->irq, brd);
}
