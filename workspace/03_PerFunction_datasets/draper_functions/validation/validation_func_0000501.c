pipe_irq_enable(struct r8a66597 *r8a66597, struct urb *urb,
			    u16 pipenum)
{
	if (pipenum == 0 && usb_pipeout(urb->pipe))
		enable_irq_empty(r8a66597, pipenum);
	else
		enable_irq_ready(r8a66597, pipenum);

	if (!usb_pipeisoc(urb->pipe))
		enable_irq_nrdy(r8a66597, pipenum);
}
