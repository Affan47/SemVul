*/
static int ql_adapter_reset(struct ql3_adapter *qdev)
{
	struct ql3xxx_port_registers __iomem *port_regs =
		qdev->mem_map_registers;
	int status = 0;
	u16 value;
	int max_wait_time;

	set_bit(QL_RESET_ACTIVE, &qdev->flags);
	clear_bit(QL_RESET_DONE, &qdev->flags);


	netdev_printk(KERN_DEBUG, qdev->ndev, "Issue soft reset to chip\n");
	ql_write_common_reg(qdev,
			    &port_regs->CommonRegs.ispControlStatus,
			    ((ISP_CONTROL_SR << 16) | ISP_CONTROL_SR));


	netdev_printk(KERN_DEBUG, qdev->ndev,
		      "Wait 10 milliseconds for reset to complete\n");


	max_wait_time = 5;
	do {
		value =
		    ql_read_common_reg(qdev,
				       &port_regs->CommonRegs.ispControlStatus);
		if ((value & ISP_CONTROL_SR) == 0)
			break;

		ssleep(1);
	} while ((--max_wait_time));


	value =
	    ql_read_common_reg(qdev, &port_regs->CommonRegs.ispControlStatus);
	if (value & ISP_CONTROL_RI) {
		netdev_printk(KERN_DEBUG, qdev->ndev,
			      "clearing RI after reset\n");
		ql_write_common_reg(qdev,
				    &port_regs->CommonRegs.
				    ispControlStatus,
				    ((ISP_CONTROL_RI << 16) | ISP_CONTROL_RI));
	}

	if (max_wait_time == 0) {

		ql_write_common_reg(qdev,
				    &port_regs->CommonRegs.
				    ispControlStatus,
				    ((ISP_CONTROL_FSR << 16) |
				     ISP_CONTROL_FSR));


		max_wait_time = 5;
		do {
			value = ql_read_common_reg(qdev,
						   &port_regs->CommonRegs.
						   ispControlStatus);
			if ((value & ISP_CONTROL_FSR) == 0)
				break;
			ssleep(1);
		} while ((--max_wait_time));
	}
	if (max_wait_time == 0)
		status = 1;

	clear_bit(QL_RESET_ACTIVE, &qdev->flags);
	set_bit(QL_RESET_DONE, &qdev->flags);
	return status;
}
