usbhsf_rx_irq_ctrl(struct usbhs_pipe *pipe, int enable)
{
	usbhsf_irq_ready_ctrl(pipe, enable);
}
