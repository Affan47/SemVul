prepare_recovery(SSCOP_DSC *dsc)
{
    if (dsc->clear_buffers) {
	clear_transmission_queue(dsc);
	clear_transmission_buffer(dsc);
    }
    clear_retransmission_queue(dsc);
}
