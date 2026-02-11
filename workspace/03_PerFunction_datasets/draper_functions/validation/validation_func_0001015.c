microdelay_init(unsigned int multiply_factor) {


#ifdef __dos__
    old_port_value=inportb(0x80);
#else
    if (geteuid()!=0) {
	fprintf(stderr,"ERROR: this programs needs root permisions to access parallel port. Please use root user to run or setuid bit.\n");
	abort();
    }
    ioperm(0x80,1,1);
    old_port_value=inb(0x80);
#endif
    m_f = multiply_factor;
}
