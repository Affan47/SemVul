qla4_82xx_interrupt_service_routine(struct scsi_qla_host *ha,
    uint32_t intr_status)
{

	if ((intr_status & HSRX_RISC_IOCB_INT) &&
	    test_bit(AF_INIT_DONE, &ha->flags))
		qla4xxx_process_response_queue(ha);


	if (intr_status & HSRX_RISC_MB_INT)
		qla4xxx_isr_decode_mailbox(ha,
		    readl(&ha->qla4_82xx_reg->mailbox_out[0]));


	writel(0, &ha->qla4_82xx_reg->host_int);
	readl(&ha->qla4_82xx_reg->host_int);
}
