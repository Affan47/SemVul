static int hardware_init_port(void)
{
	u8 scratch, scratch2, scratch3;


	scratch = sinp(UART_IER);
	soutp(UART_IER, 0);
#ifdef __i386__
	outb(0xff, 0x080);
#endif
	scratch2 = sinp(UART_IER) & 0x0f;
	soutp(UART_IER, 0x0f);
#ifdef __i386__
	outb(0x00, 0x080);
#endif
	scratch3 = sinp(UART_IER) & 0x0f;
	soutp(UART_IER, scratch);
	if (scratch2 != 0 || scratch3 != 0x0f) {

		pr_err("port existence test failed, cannot continue\n");
		return -ENODEV;
	}


	soutp(UART_LCR, sinp(UART_LCR) & (~UART_LCR_DLAB));


	soutp(UART_IER, sinp(UART_IER) &
	      (~(UART_IER_MSI | UART_IER_RLSI | UART_IER_THRI | UART_IER_RDI)));


	sinp(UART_LSR);
	sinp(UART_RX);
	sinp(UART_IIR);
	sinp(UART_MSR);


	off();


	sinp(UART_LSR);
	sinp(UART_RX);
	sinp(UART_IIR);
	sinp(UART_MSR);

	switch (type) {
	case IR_IRDEO:
	case IR_IRDEO_REMOTE:


		soutp(UART_LCR, sinp(UART_LCR) | UART_LCR_DLAB);

		soutp(UART_DLM, 0);
		soutp(UART_DLL, 1);

		soutp(UART_LCR, UART_LCR_WLEN7);

		break;
	default:
		break;
	}

	return 0;
}
