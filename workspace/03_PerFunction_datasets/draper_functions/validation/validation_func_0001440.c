esas2r_handle_chip_rst_during_tasklet(struct esas2r_adapter *a)
{
	while (test_bit(AF_CHPRST_DETECTED, &a->flags)) {


		if (!test_bit(AF_DEGRADED_MODE, &a->flags) &&
		    !test_bit(AF_POWER_MGT, &a->flags))
			esas2r_disable_chip_interrupts(a);


		esas2r_check_adapter(a);
		esas2r_init_adapter_hw(a, 0);

		if (test_bit(AF_CHPRST_NEEDED, &a->flags))
			break;

		if (test_bit(AF_POWER_MGT, &a->flags)) {

			if (test_bit(AF_FIRST_INIT, &a->flags)) {

				esas2r_log(ESAS2R_LOG_CRIT,
					   "The firmware was reset during a normal power-up sequence");
			} else {

				clear_bit(AF_POWER_MGT, &a->flags);
				esas2r_send_reset_ae(a, true);
			}
		} else {

			if (test_bit(AF_FIRST_INIT, &a->flags)) {

			} else {

				esas2r_send_reset_ae(a, false);
			}

			esas2r_log(ESAS2R_LOG_CRIT,
				   "Recovering from a chip reset while the chip was online");
		}

		clear_bit(AF_CHPRST_STARTED, &a->flags);
		esas2r_enable_chip_interrupts(a);


		clear_bit(AF_CHPRST_DETECTED, &a->flags);
	}
}
