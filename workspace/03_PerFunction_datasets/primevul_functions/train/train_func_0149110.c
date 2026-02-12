static int pn533_acr122_rx_frame_size(void *frame)
{
	struct pn533_acr122_rx_frame *f = frame;


	return sizeof(struct pn533_acr122_rx_frame) + f->ccid.datalen;
}
